import { ValidationError, ValidationPipe } from '@nestjs/common';
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { InvalidParametersExceptionFilter } from './validation/invalid-parameters-exception-filter copy';
import { ValidationException } from './validation/validation-exception';
import { ValidationExceptionFilter } from './validation/validation-exception-filter';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  app.useGlobalFilters(new ValidationExceptionFilter(), new InvalidParametersExceptionFilter())
  app.useGlobalPipes(new ValidationPipe({
    whitelist: true,
    exceptionFactory: (errors: ValidationError[]) => new ValidationException(errors)
  }))
  app.enableCors({
    origin: "http://localhost:3000",
    methods: "*",
    credentials: false
  })
  await app.listen(3000);
}
bootstrap();
