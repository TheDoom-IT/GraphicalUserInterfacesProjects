export type ErrorResponse = {
    statusCode: number;
    errors: ErrorsObject
}

export type ErrorsObject = {
    [key: string]: string
}