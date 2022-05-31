import { Body, Controller, Delete, ForbiddenException, Get, HttpCode, HttpStatus, Param, Patch, Post, Request, UseGuards } from "@nestjs/common";
import { JwtAuthGuard } from "src/auth/jwt-auth.guard";
import { BlogEntryDto, BlogEntryDtoCreate, BlogEntryDtoUpdate, blogEntryEntityToDto } from "src/dtos/blog-enry.dto";
import { BlogEntryService } from "./blog-entry.service";

@Controller('blogs/:blogId/entries')
export class BlogEntryController {
    constructor(
        private readonly blogEntryService: BlogEntryService
    ) { }

    @Get()
    async index(@Param('blogId') blogId: number): Promise<BlogEntryDto[]> {
        const entryEntities = await this.blogEntryService.getAll(blogId)
        return entryEntities.map(entry => blogEntryEntityToDto(entry))
    }

    @Get(':id')
    async show(@Param('blogId') blogId: number, @Param('id') id: number): Promise<BlogEntryDto> {
        const entryEntity = await this.blogEntryService.getOne(blogId, id);
        return blogEntryEntityToDto(entryEntity)
    }

    @Get('private/:id')
    @UseGuards(JwtAuthGuard)
    async privateShow(@Request() req, @Param('blogId') blogId: number, @Param('id') id: number): Promise<BlogEntryDto> {
        const entryEntity = await this.blogEntryService.getOne(blogId, id);
        if (req.user.id != entryEntity.blog.owner.id) {
            throw new ForbiddenException()
        }
        return blogEntryEntityToDto(entryEntity)
    }

    @Post()
    @HttpCode(HttpStatus.CREATED)
    @UseGuards(JwtAuthGuard)
    async create(@Request() req, @Body() body: BlogEntryDtoCreate, @Param('blogId') blogId: number): Promise<BlogEntryDto> {
        const entryEntity = await this.blogEntryService.create(req.user, body, blogId);
        return blogEntryEntityToDto(entryEntity)
    }

    @Patch(':id')
    @HttpCode(HttpStatus.OK)
    @UseGuards(JwtAuthGuard)
    async update(@Request() req, @Body() body: BlogEntryDtoUpdate, @Param('blogId') blogId: number, @Param('id') id: number): Promise<BlogEntryDto> {
        const entryEntity = await this.blogEntryService.update(req.user, body, blogId, id)
        return blogEntryEntityToDto(entryEntity)
    }

    @Delete(':id')
    @HttpCode(HttpStatus.NO_CONTENT)
    @UseGuards(JwtAuthGuard)
    async delete(@Request() req, @Param('blogId') blogId: number, @Param('id') id: number): Promise<void> {
        await this.blogEntryService.delete(req.user, blogId, id)
    }
}
