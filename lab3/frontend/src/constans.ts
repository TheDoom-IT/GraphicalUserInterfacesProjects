export const API_URL = "http://localhost:4000"

export const API_LOGIN = `${API_URL}/login`
export const API_REGISTER = `${API_URL}/register`
export const API_CURRENT_USER = `${API_URL}/current_user`

export const API_BLOG = `${API_URL}/blogs`
export const API_PRIVATE_BLOG = `${API_BLOG}/private`

export const API_BLOGS_SHOW = (id: number | string) => `${API_BLOG}/${id}`
export const API_BLOGS_DELETE = (id: number | string) => `${API_BLOG}/${id}`
export const API_BLOGS_CREATE = `${API_BLOG}`
export const API_PRIVATE_BLOG_SHOW = (id: number | string) => `${API_PRIVATE_BLOG}/${id}`
export const API_BLOGS_UPDATE = (id: number | string) => `${API_BLOG}/${id}`

export const API_ENTRIES = (blogId: number | string) => `${API_URL}/blogs/${blogId}/entries`
export const API_PRIVATE_ENTRIES = (blogId: number | string) => `${API_URL}/blogs/${blogId}/entries/private`
export const API_PRIVATE_BLOG_ENTRIES_SHOW = (blogId: number | string, id: number | string) => `${API_PRIVATE_ENTRIES(blogId)}/${id}`

export const API_ENTRIES_UPDATE = (blogId: number | string, id: number | string) => `${API_URL}/blogs/${blogId}/entries/${id}`
export const API_ENTRIES_CREATE = (blogId: number | string) => `${API_ENTRIES(blogId)}`
export const API_ENTRIES_DELETE = (blogId: number | string, id: number | string) => `${API_ENTRIES(blogId)}/${id}`


export const BASIC_HEADER = {
    'Content-Type': 'application/json'
}