import { Entity, Column, PrimaryGeneratedColumn, ManyToOne, CreateDateColumn } from 'typeorm';
import { BlogEntity } from './blog.entity';

export type BlogEntryEntityCreate = Pick<BlogEntryEntity, "title" | "content"> & { blog: { id: number } }
export type BlogEntryEntityUpdate = Pick<BlogEntryEntity, "id" | "title" | "content">

@Entity()
export class BlogEntryEntity {
    @PrimaryGeneratedColumn()
    id: number;

    @Column({ nullable: false })
    title: string;

    @CreateDateColumn()
    datetime: Date

    @Column({ nullable: false })
    content: string;

    @ManyToOne(() => BlogEntity, (blog) => blog.entries, { nullable: false, onDelete: 'CASCADE' })
    blog: BlogEntity
}