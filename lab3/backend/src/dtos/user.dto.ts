import { PickType } from "@nestjs/mapped-types";
import { IsEmail, IsNotEmpty, MinLength } from "class-validator";
import { UserEntitySafe } from "src/entities/user.entity";

class UserDto {
    id: number

    @MinLength(5, {
        message: "Login should be at least 5 characters long"
    })
    @IsNotEmpty({
        message: "Login can't be empty"
    })
    login: string;

    @IsEmail({}, {
        message: "Email should be a valid email"
    })
    @IsNotEmpty({
        message: "Email can't be empty"
    })
    email: string;

    @MinLength(8, {
        message: "Password should be at least 8 characters long"
    })
    @IsNotEmpty({
        message: "Password can't be empty"
    })
    password: string;
}

export class UserDtoSafe extends PickType(UserDto, ['id', 'login', 'email'] as const) { }
export class UserDtoCreate extends PickType(UserDto, ['login', 'email', 'password'] as const) { }
export class UserDtoCreated extends PickType(UserDto, ['login', 'email'] as const) { }
export class UserDtoLogin extends PickType(UserDto, ['login', 'password'] as const) { }

export function userEntitySafetoUserDtoSafe(user: UserEntitySafe): UserDtoSafe {
    return {
        id: user.id,
        login: user.login,
        email: user.email
    }
}