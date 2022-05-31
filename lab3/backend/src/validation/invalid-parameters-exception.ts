import { HttpException, HttpStatus } from "@nestjs/common";
import { ErrorsObject } from "src/helpers/types";

export class InvalidParametersException extends HttpException {
    constructor(errors: ErrorsObject) {
        super('Invalid parameters', HttpStatus.BAD_REQUEST)
        this.errors = errors
    }

    public errors: ErrorsObject;
}