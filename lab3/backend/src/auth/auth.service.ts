import { Injectable } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import { InjectRepository } from '@nestjs/typeorm';
import { UserEntitySafe, UserEntity } from 'src/entities/user.entity';
import { Repository } from 'typeorm';

@Injectable()
export class AuthService {
    constructor(
        @InjectRepository(UserEntity)
        private readonly usersRepository: Repository<UserEntity>,
        private readonly jwtService: JwtService) { }

    async validateUser(username: string, password: string): Promise<UserEntitySafe | null> {
        const user = await this.usersRepository.findOne({
            where: {
                login: username,
                password: password
            }
        })

        if (user) {
            return user
        }
        return null
    }

    async login(user: UserEntitySafe) {
        const payload = { sub: user.id }
        return {
            access_token: this.jwtService.sign(payload),
            user: {
                id: user.id,
                login: user.login,
                email: user.email
            }
        }
    }
}
