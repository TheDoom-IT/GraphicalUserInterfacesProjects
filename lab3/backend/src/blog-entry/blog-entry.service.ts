import { ForbiddenException, Injectable, NotFoundException } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { BlogEntryDtoCreate, BlogEntryDtoUpdate } from 'src/dtos/blog-enry.dto';
import { BlogEntryEntity, BlogEntryEntityCreate } from 'src/entities/blog-entry';
import { BlogEntity } from 'src/entities/blog.entity';
import { UserEntitySafe } from 'src/entities/user.entity';
import { Repository } from 'typeorm';

@Injectable()
export class BlogEntryService {
  constructor(
    @InjectRepository(BlogEntryEntity)
    private blogEntriesRepository: Repository<BlogEntryEntity>,
    @InjectRepository(BlogEntity)
    private blogsRepository: Repository<BlogEntity>
  ) { }

  async getAll(blogId: number): Promise<BlogEntryEntity[]> {
    const blog = await this.blogsRepository.findOne(blogId)
    if (!blog) {
      throw new NotFoundException()
    }

    const entries = await this.blogEntriesRepository.find({
      where: {
        blog: {
          id: blogId
        }
      },
      relations: ['blog', 'blog.owner'],
      order: {
        datetime: 'DESC'
      }
    })

    return entries
  }

  async getOne(blogId: number, id: number): Promise<BlogEntryEntity> {
    const entry = await this.blogEntriesRepository.findOne(id, {
      where: {
        blog: {
          id: blogId
        }
      },
      relations: ['blog', 'blog.owner']
    })
    if (!entry) {
      throw new NotFoundException()
    }

    return entry
  }

  async create(currentUser: UserEntitySafe, entry: BlogEntryDtoCreate, blogId: number): Promise<BlogEntryEntity> {
    const blog = await this.blogsRepository.findOne(blogId, {
      where: {
        owner: {
          id: currentUser.id
        }
      },
      relations: ['owner']
    })

    if (!blog) {
      throw new ForbiddenException()
    }

    const toCreate: BlogEntryEntityCreate = {
      ...entry,
      blog: {
        id: blogId
      }
    }

    const result = await this.blogEntriesRepository.save(toCreate)
    return {
      ...result,
      blog: blog
    }
  }

  async update(currentUser: UserEntitySafe, entry: BlogEntryDtoUpdate, blogId: number, entryId: number): Promise<BlogEntryEntity> {
    const blogEntry = await this.blogEntriesRepository.findOne(entryId, {
      where: {
        blog: {
          id: blogId,
          owner: {
            id: currentUser.id
          }
        }
      },
      relations: ['blog', 'blog.owner']
    })

    if (!blogEntry) {
      throw new ForbiddenException()
    }

    blogEntry.content = entry.content
    blogEntry.title = entry.title
    const result = await this.blogEntriesRepository.save(blogEntry)
    return result
  }

  async delete(currentUser: UserEntitySafe, blogId: number, entryId: number): Promise<void> {
    const blogEntry = await this.blogEntriesRepository.findOne(entryId, {
      where: {
        blog: {
          id: blogId,
          owner: {
            id: currentUser.id
          }
        }
      }
    })

    if (!blogEntry) {
      throw new ForbiddenException()
    }

    await this.blogEntriesRepository.delete(entryId)
  }
}