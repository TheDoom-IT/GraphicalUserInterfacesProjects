import { Entity, Column, PrimaryGeneratedColumn, OneToMany, ManyToOne } from 'typeorm';
import { BlogEntryEntity } from './blog-entry';
import { UserEntitySafe, UserEntity } from './user.entity';

export type BlogEntityCreate = Pick<BlogEntity, "title"> & { owner: UserEntitySafe }

@Entity()
export class BlogEntity {
    @PrimaryGeneratedColumn()
    id: number;

    @Column({ nullable: false, unique: true })
    title: string;

    @ManyToOne(() => UserEntity, (user) => user.blogs, { nullable: false, onDelete: 'CASCADE' })
    owner: UserEntity;

    @OneToMany(() => BlogEntryEntity, entry => entry.blog)
    entries: BlogEntryEntity[];
}