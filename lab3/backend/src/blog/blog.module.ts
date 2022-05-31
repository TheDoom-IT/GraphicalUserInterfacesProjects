import { Module } from "@nestjs/common";
import { TypeOrmModule } from "@nestjs/typeorm";
import { AuthModule } from "src/auth/auth.module";
import { BlogEntity } from "src/entities/blog.entity";
import { BlogController } from "./blog.controller";
import { BlogService } from "./blog.service";


@Module({
  imports: [TypeOrmModule.forFeature([BlogEntity]), AuthModule],
  controllers: [BlogController],
  providers: [BlogService]
})
export class BlogModule { }
