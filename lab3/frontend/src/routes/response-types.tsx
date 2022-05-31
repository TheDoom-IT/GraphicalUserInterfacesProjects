export type ResponseCurrentUser = {
    id: number
    login: string
    email: string
}

export type ResponseLogin = {
    access_token?: string
    user?: User
    errors?: {
        general?: string
    }
}

export type ResponseBlogsIndex = Blog[]

export type Blog = {
    id: number
    title: string
    ownerId: number
}

export type User = {
    id: number
    login: string
    email: string
}

export type ResponseBlogsCreate = {
    id?: number
    title?: string
    ownerId?: string
    errors?: {
        title?: string
    }
}

export type ResponseBlogsShow = Blog

export type ResponseBlogsUpdate = {
    id: number
    title: string
    ownerId: number
    errors?: {
        title?: string
    }
}

export type Entry = {
    id: number
    title: string
    content: string
    datetime: string
    blogId: number
    ownerId: number
}

export type ResponseEntriesShow = Entry
export type ResponseEntriesIndex = Entry[]

export type ResponseEntriesUpdate = Entry & {
    errors?: {
        title: string
        content: string
    }
}

export type ResponseEntriesCreate = Entry & {
    errors?: {
        title: string
        content: string
    }
}