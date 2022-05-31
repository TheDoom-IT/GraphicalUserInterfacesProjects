import { ArgumentsHost, Catch, ExceptionFilter } from "@nestjs/common";
import { Response } from "express";
import { InvalidParametersException } from "./invalid-parameters-exception";


@Catch(InvalidParametersException)
export class InvalidParametersExceptionFilter implements ExceptionFilter {
    catch(exception: InvalidParametersException, host: ArgumentsHost) {
        const ctx = host.switchToHttp();
        const response = ctx.getResponse<Response>();
        const status = exception.getStatus();

        response
            .status(status)
            .json({
                statusCode: status,
                errors: exception.errors
            });
    }
}