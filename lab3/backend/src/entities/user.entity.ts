import { Entity, Column, PrimaryGeneratedColumn, OneToMany } from 'typeorm';
import { BlogEntity } from './blog.entity';

export type UserEntityCreate = Pick<UserEntity, "login" | "email" | "password">

export type UserEntitySafe = Pick<UserEntity, "id" | "login" | "email">

@Entity()
export class UserEntity {
    @PrimaryGeneratedColumn()
    id: number;

    @Column({ nullable: false, unique: true })
    login: string;

    @Column({ nullable: false })
    email: string;

    @Column({ nullable: false, select: false })
    password: string;

    @OneToMany(type => BlogEntity, blog => blog.owner)
    blogs: BlogEntity[];
}

export function userEntityToEntitySafe(user: UserEntity): UserEntitySafe {
    return {
        id: user.id,
        login: user.login,
        email: user.email
    }
}