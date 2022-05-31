import { Body, Controller, Get, HttpCode, HttpStatus, Post, Request, Res, UseGuards } from '@nestjs/common';
import { Response } from 'express';
import { AuthService } from 'src/auth/auth.service';
import { JwtAuthGuard } from 'src/auth/jwt-auth.guard';
import { LocalAuthGuard } from 'src/auth/local-auth.guard';
import { UserDtoCreate, UserDtoSafe, userEntitySafetoUserDtoSafe } from 'src/dtos/user.dto';
import { UserService } from './user.service';

@Controller()
export class UserController {
  constructor(
    private readonly authService: AuthService,
    private readonly userService: UserService
  ) { }

  @Get('users')
  async getUsers(): Promise<UserDtoSafe[]> {
    const users = await this.userService.getUsers()
    return users.map(user => userEntitySafetoUserDtoSafe(user))
  }

  @UseGuards(JwtAuthGuard)
  @Get('current_user')
  async getCurrent(@Request() req): Promise<UserDtoSafe> {
    return req.user
  }

  @UseGuards(LocalAuthGuard)
  @HttpCode(HttpStatus.OK)
  @Post('login')
  async login(@Request() req): Promise<{ access_token: string }> {
    return this.authService.login(req.user);
  }

  @Post("register")
  @HttpCode(HttpStatus.CREATED)
  async register(@Res({ passthrough: true }) res: Response, @Body() createUserDto: UserDtoCreate): Promise<UserDtoSafe> {
    const user = await this.userService.register(createUserDto)

    return userEntitySafetoUserDtoSafe(user)
  }
}
