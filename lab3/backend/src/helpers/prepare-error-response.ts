import { HttpStatus } from "@nestjs/common";
import { ErrorResponse, ErrorsObject } from "./types";

export function prepareErrorResponse(errors: ErrorsObject): ErrorResponse {
    return {
        statusCode: HttpStatus.BAD_REQUEST,
        errors
    }
}