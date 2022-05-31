import { Strategy } from 'passport-local';
import { PassportStrategy } from '@nestjs/passport';
import { Injectable } from '@nestjs/common';
import { AuthService } from 'src/auth/auth.service';
import { UserEntitySafe } from 'src/entities/user.entity';
import { InvalidParametersException } from 'src/validation/invalid-parameters-exception';

@Injectable()
export class LocalStrategy extends PassportStrategy(Strategy) {
    constructor(private authService: AuthService) {
        super({ usernameField: 'login' });
    }

    async validate(username: string, password: string): Promise<UserEntitySafe> {
        const user = await this.authService.validateUser(username, password);
        if (!user) {
            const errors = {
                general: "Invalid username and/or password"
            }
            throw new InvalidParametersException(errors);
        }
        return user;
    }
}