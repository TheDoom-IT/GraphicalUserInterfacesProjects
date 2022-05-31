import { PickType } from "@nestjs/mapped-types";
import { IsNotEmpty, IsNumber, IsOptional, IsPositive, MinLength } from "class-validator";
import { BlogEntity } from "src/entities/blog.entity";

export class BlogDto {
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

    @IsPositive({
        message: "OwnerId should be a positive number"
    })
    @IsNumber({}, {
        message: "OwnerId should be a number"
    })
    @IsNotEmpty({
        message: "OwnerId can't be empty"
    })
    ownerId: number;
}

export class BlogDtoGet extends PickType(BlogDto, []) {
    @IsPositive({
        message: "OwnerId should be a positive number"
    })
    @IsNumber({}, {
        message: "OwnerId should be a number"
    })
    @IsOptional()
    ownerId?: number;
}
export class BlogDtoCreate extends PickType(BlogDto, ['title'] as const) { }
export class BlogDtoUpdate extends PickType(BlogDto, ['title'] as const) { }

export function blogEntityToDto(blog: BlogEntity): BlogDto {
    return {
        id: blog.id,
        title: blog.title,
        ownerId: blog.owner.id
    }
}