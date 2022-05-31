import { ForbiddenException, Injectable, NotFoundException } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { BlogDtoCreate, BlogDtoGet, BlogDtoUpdate } from 'src/dtos/blog.dto';
import { BlogEntity, BlogEntityCreate } from 'src/entities/blog.entity';
import { UserEntitySafe } from 'src/entities/user.entity';
import { InvalidParametersException } from 'src/validation/invalid-parameters-exception';
import { FindManyOptions, Repository } from 'typeorm';

@Injectable()
export class BlogService {
  constructor(
    @InjectRepository(BlogEntity)
    private blogsRepository: Repository<BlogEntity>
  ) { }

  async getAll(blog: BlogDtoGet): Promise<BlogEntity[]> {
    const options: FindManyOptions<BlogEntity> = { relations: ['owner'], order: { id: "DESC" } }
    if (blog.ownerId) {
      options['where'] = {
        owner: {
          id: blog.ownerId
        }
      }
    }

    return await this.blogsRepository.find(options);
  }

  async getOne(id: number): Promise<BlogEntity> {
    const blog = await this.blogsRepository.findOne(id, { relations: ['owner'] })
    if (!blog) {
      throw new NotFoundException()
    }
    return blog
  }

  async create(currentUser: UserEntitySafe, blog: BlogDtoCreate): Promise<BlogEntity> {
    const otherBlog = await this.blogsRepository.findOne({ where: { title: blog.title } })
    if (otherBlog) {
      const errors = {
        title: "Blog with a given title already exists"
      }

      throw new InvalidParametersException(errors)
    }

    const createBlog: BlogEntityCreate = {
      ...blog,
      owner: currentUser
    }

    const result = await this.blogsRepository.save(createBlog)
    return result
  }

  async update(currentUser: UserEntitySafe, blogId: number, updateBlog: BlogDtoUpdate): Promise<BlogEntity> {
    let blog = await this.blogsRepository.findOne(
      blogId,
      {
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

    const blogWithTitle = await this.blogsRepository.findOne({
      where: {
        title: updateBlog.title
      }
    })

    if (blogWithTitle && blogWithTitle.id != blogId) {
      const errors = {
        title: "Blog with a given title already exists"
      }
      throw new InvalidParametersException(errors)
    }

    blog.title = updateBlog.title
    const result = await this.blogsRepository.save(blog)

    return result
  }

  async delete(currentUser: UserEntitySafe, blogId: number): Promise<void> {
    let blog = await this.blogsRepository.findOne(
      blogId,
      {
        where: {
          owner: {
            id: currentUser.id
          }
        }, relations: ['owner']
      })

    if (!blog) {
      throw new ForbiddenException()
    }

    await this.blogsRepository.delete(blog)
  }
}
