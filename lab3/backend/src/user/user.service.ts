import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { UserDtoCreate } from 'src/dtos/user.dto';
import { UserEntity, UserEntitySafe, userEntityToEntitySafe } from 'src/entities/user.entity';
import { InvalidParametersException } from 'src/validation/invalid-parameters-exception';
import { Repository } from 'typeorm';

@Injectable()
export class UserService {
  constructor(
    @InjectRepository(UserEntity)
    private usersRepository: Repository<UserEntity>
  ) { }

  async getUsers(): Promise<UserEntitySafe[]> {
    return this.usersRepository.find()
  }

  async register(newUser: UserDtoCreate): Promise<UserEntitySafe> {
    const user = await this.usersRepository.findOne({
      where: [
        { login: newUser.login },
        { email: newUser.email }
      ]
    })

    if (user) {
      let errors = {}
      if (user.login == newUser.login) {
        errors['login'] = "This login is already taken"
      }
      if (user.email == newUser.email) {
        errors['email'] = "This email is already taken"
      }
      throw new InvalidParametersException(errors)
    }

    const result = await this.usersRepository.save(newUser)

    return userEntityToEntitySafe(result)
  }
}
