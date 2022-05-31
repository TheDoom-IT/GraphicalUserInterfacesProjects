export const PATH_USER_PROFILE = "/profile"
export const PATH_LOGGED_OUT = "/logged_out"
export const PATH_LOGIN = "/login"
export const PATH_REGISTER = "/register"
export const PATH_NOT_FOUND = "/not_found"
export const PATH_FORBIDDEN = "/forbidden"

export const PATH_BLOGS = '/blogs'
export const PATH_BLOGS_SHOW = '/blogs/:id'
export const PATH_BLOGS_EDIT = '/blogs/:id/edit'
export const PATH_BLOGS_NEW = '/blogs/new'

export const PATH_BLOGS_SHOW_PARAM = (id: number | string) => `${PATH_BLOGS}/${id}`
export const PATH_BLOGS_EDIT_PARAM = (id: number) => `${PATH_BLOGS}/${id}/edit`

export const PATH_ENTRIES = `${PATH_BLOGS}/:blogId/entries`
export const PATH_ENTRIES_SHOW = `${PATH_ENTRIES}/:id`
export const PATH_ENTRIES_EDIT = `${PATH_ENTRIES}/:id/edit`
export const PATH_ENTRIES_NEW = `${PATH_ENTRIES}`
export const PATH_ENTRIES_SHOW_PARAM = (blogId: number | string, id: number | string) => `${PATH_BLOGS}/${blogId}/entries/${id}`
export const PATH_ENTRIES_EDIT_PARAM = (blogId: number | string, id: number | string) => `${PATH_BLOGS}/${blogId}/entries/${id}/edit`
export const PATH_ENTIRES_NEW_PARAM = (blogId: number | string) => `${PATH_BLOGS}/${blogId}/entries`