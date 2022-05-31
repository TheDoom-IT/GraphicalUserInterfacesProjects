import { ArgumentsHost, Catch, ExceptionFilter } from "@nestjs/common";
import { Response } from "express";
import { ValidationException } from "./validation-exception";


@Catch(ValidationException)
export class ValidationExceptionFilter implements ExceptionFilter {
    catch(exception: ValidationException, host: ArgumentsHost) {
        const ctx = host.switchToHttp();
        const response = ctx.getResponse<Response>();
        const status = exception.getStatus();

        let errors = {}

        exception.errors.forEach((error) => {
            let field = error.property
            let firstKey = Object.keys(error.constraints)[0]
            let message = error.constraints[firstKey]

            errors[field] = message
        })

        response
            .status(status)
            .json({
                statusCode: status,
                errors: errors
            });
    }
}