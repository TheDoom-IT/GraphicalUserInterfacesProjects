const KEY = 'jwt_token'

export function saveJWT(token: string) {
    localStorage.setItem(KEY, token)
}

export function getJWT(headers: any) {
    headers.Authorization = `Bearer ${localStorage.getItem(KEY)}`
    return headers
}

export function removeJWT() {
    localStorage.removeItem(KEY)
}

export function isJWTsaved() {
    return localStorage.getItem(KEY) != null
}