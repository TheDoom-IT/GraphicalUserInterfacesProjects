import { HttpException, HttpStatus, ValidationError } from "@nestjs/common";

export class ValidationException extends HttpException {
    constructor(errors: ValidationError[]) {
        super('Invalid parameters', HttpStatus.BAD_REQUEST)
        this.errors = errors
    }

    public errors: ValidationError[];
}