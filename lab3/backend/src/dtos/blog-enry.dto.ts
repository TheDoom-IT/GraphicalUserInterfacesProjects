import { PickType } from "@nestjs/mapped-types";
import { IsNotEmpty, IsNumber, IsPositive, MinLength } from "class-validator";
import { BlogEntryEntity } from "src/entities/blog-entry";

export class BlogEntryDto {
    @IsPositive({
        message: "Id should be a positive number"
    })
    @IsNumber({}, {
        message: "Id should be a number"
    })
    @IsNotEmpty({
        message: "Id can't be empty"
    })
    id: number

    @MinLength(5, {
        message: "Title should be at least 5 characters long"
    })
    @IsNotEmpty({
        message: "Title can't be empty"
    })
    title: string;

    @MinLength(10, {
        message: "Content should be at least 10 characters long"
    })
    @IsNotEmpty({
        message: "Content can't be empty"
    })
    content: string;

    @IsPositive({
        message: "BlogId should be a positive number"
    })
    @IsNumber({}, {
        message: "BlogId should be a number"
    })
    @IsNotEmpty({
        message: "BlogId can't be empty"
    })
    blogId: number;

    datetime: Date;

    ownerId: number;
}

export class BlogEntryDtoCreate extends PickType(BlogEntryDto, ['title', 'content'] as const) { }
export class BlogEntryDtoUpdate extends PickType(BlogEntryDto, ['title', 'content'] as const) { }

export function blogEntryEntityToDto(entry: BlogEntryEntity): BlogEntryDto {
    return {
        id: entry.id,
        title: entry.title,
        content: entry.content,
        datetime: entry.datetime,
        blogId: entry.blog.id,
        ownerId: entry.blog.owner.id
    }
}