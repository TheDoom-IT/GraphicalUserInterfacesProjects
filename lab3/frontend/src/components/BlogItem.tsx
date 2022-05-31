import { Link } from "react-router-dom"
import { PATH_BLOGS_EDIT_PARAM, PATH_BLOGS_SHOW_PARAM } from "../routes/constants"
import { Blog } from "../routes/response-types"

export type BlogItemProps = {
    blog: Blog
    onDeleteClick: (blog: Blog) => void
}
export function BlogItem(props: BlogItemProps) {
    return (
        <div className="card">
            <div className="card-header">
                <div>
                    <Link className="card-title" to={PATH_BLOGS_SHOW_PARAM(props.blog.id)}>{props.blog.title}</Link>
                </div>
                <div>
                    <Link className="btn" to={PATH_BLOGS_EDIT_PARAM(props.blog.id)}>Edit</Link>
                    <button className="btn btn-red" onClick={() => props.onDeleteClick(props.blog)}>Delete</button>
                </div>
            </div>
        </div>
    )
}