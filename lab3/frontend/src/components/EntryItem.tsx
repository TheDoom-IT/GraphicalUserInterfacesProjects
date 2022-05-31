import { Link } from "react-router-dom"
import { PATH_ENTRIES_EDIT_PARAM, PATH_ENTRIES_SHOW_PARAM } from "../routes/constants"
import { Entry } from "../routes/response-types"

export type EntryItemProps = {
    entry: Entry
    onDeleteClick: (entry: Entry) => void
}
export function EntryItem(props: EntryItemProps) {
    return (
        <div className="card" >
            <div className="card-header">
                <div>
                    <Link className="card-title" to={PATH_ENTRIES_SHOW_PARAM(props.entry.blogId, props.entry.id)}>{props.entry.title}</Link>
                </div>
                <div>
                    <Link className="btn" to={PATH_ENTRIES_EDIT_PARAM(props.entry.blogId, props.entry.id)}>Edit</Link>
                    <button className="btn btn-red" onClick={() => props.onDeleteClick(props.entry)}>Delete</button>
                </div>
            </div>
            <div className="card-content">
                <p>{(new Date(props.entry.datetime)).toLocaleDateString()}</p>
                {props.entry.content.slice(0, 300) + '...'}
            </div>
        </div>
    )
}