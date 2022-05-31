import { Module } from '@nestjs/common';
import { ConfigModule, ConfigService } from '@nestjs/config';
import { TypeOrmModule } from '@nestjs/typeorm';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { BlogEntryEntity } from './entities/blog-entry';
import { BlogEntity } from './entities/blog.entity';
import { UserEntity } from './entities/user.entity';
import { UserModule } from './user/user.module';
import { AuthModule } from './auth/auth.module';
import { BlogModule } from './blog/blog.module';
import { BlogEntryModule } from './blog-entry/blog-entry.module';

const ENV = process.env.NODE_ENV

@Module({
  imports: [
    AuthModule,
    UserModule,
    BlogModule,
    BlogEntryModule,
    ConfigModule.forRoot({
      envFilePath: !ENV ? '.env' : `.env.${ENV}`
    }),
    TypeOrmModule.forRootAsync({
      imports: [ConfigModule],
      useFactory: (configService: ConfigService) => ({
        type: 'postgres',
        host: configService.get('DB_HOST'),
        port: configService.get('DB_PORT'),
        username: configService.get('DB_USERNAME'),
        password: configService.get('DB_PASSWORD'),
        database: configService.get('DB_DB_NAME'),
        entities: [UserEntity, BlogEntity, BlogEntryEntity],
        synchronize: true,
      }),
      inject: [ConfigService]
    }
    ),
    AuthModule
  ],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule { }
