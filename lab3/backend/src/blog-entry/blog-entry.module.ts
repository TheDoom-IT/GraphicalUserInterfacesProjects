import { Module } from "@nestjs/common";
import { TypeOrmModule } from "@nestjs/typeorm";
import { AuthModule } from "src/auth/auth.module";
import { BlogEntryEntity } from "src/entities/blog-entry";
import { BlogEntity } from "src/entities/blog.entity";
import { BlogEntryController } from "./blog-entry.controller";
import { BlogEntryService } from "./blog-entry.service";


@Module({
  imports: [TypeOrmModule.forFeature([BlogEntryEntity, BlogEntity]), AuthModule],
  controllers: [BlogEntryController],
  providers: [BlogEntryService]
})
export class BlogEntryModule { }
