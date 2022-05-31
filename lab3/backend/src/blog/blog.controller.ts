import { Body, Controller, Delete, ForbiddenException, Get, HttpCode, HttpStatus, Param, Patch, Post, Request, Res, UseGuards } from "@nestjs/common";
import { JwtAuthGuard } from "src/auth/jwt-auth.guard";
import { BlogDto, BlogDtoCreate, BlogDtoGet, BlogDtoUpdate, blogEntityToDto } from "src/dtos/blog.dto";
import { BlogService } from "./blog.service";

@Controller('blogs')
export class BlogController {
  constructor(
    private readonly blogService: BlogService
  ) { }

  @Get()
  async index(@Body() body: BlogDtoGet): Promise<BlogDto[]> {
    const blogEntities = await this.blogService.getAll(body)
    return blogEntities.map(blog => blogEntityToDto(blog))
  }

  @Get('private')
  @UseGuards(JwtAuthGuard)
  async privateIndex(@Request() req): Promise<BlogDto[]> {
    const body: BlogDtoGet = {
      ownerId: req.user.id
    }
    const blogEntities = await this.blogService.getAll(body)
    return blogEntities.map(blog => blogEntityToDto(blog))
  }

  @Get('private/:id')
  @UseGuards(JwtAuthGuard)
  async privateShow(@Request() req, @Param('id') id: number): Promise<BlogDto> {
    const blogEntity = await this.blogService.getOne(id);
    if (req.user.id != blogEntity.owner.id) {
      throw new ForbiddenException()
    }
    return blogEntityToDto(blogEntity)
  }

  @Get(':id')
  async show(@Param('id') id: number): Promise<BlogDto> {
    const blogEntity = await this.blogService.getOne(id)
    return blogEntityToDto(blogEntity)
  }

  @Post()
  @HttpCode(HttpStatus.CREATED)
  @UseGuards(JwtAuthGuard)
  async create(@Request() req, @Body() body: BlogDtoCreate): Promise<BlogDto> {
    const blogEntity = await this.blogService.create(req.user, body)
    return blogEntityToDto(blogEntity)
  }

  @Patch(':id')
  @HttpCode(HttpStatus.OK)
  @UseGuards(JwtAuthGuard)
  async update(@Request() req, @Param() params, @Body() body: BlogDtoUpdate): Promise<BlogDto> {
    const blogEntity = await this.blogService.update(req.user, params.id, body)
    return blogEntityToDto(blogEntity)
  }

  @Delete(':id')
  @HttpCode(HttpStatus.NO_CONTENT)
  @UseGuards(JwtAuthGuard)
  async delete(@Request() req, @Param('id') id: number): Promise<void> {
    await this.blogService.delete(req.user, id)
  }
}
