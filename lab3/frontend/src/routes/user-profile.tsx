import { StatusCodes } from "http-status-codes"
import { useContext, useEffect, useState } from "react"
import { Link, useNavigate } from "react-router-dom"
import { SessionContext, SessionContextType } from "../App"
import { BlogItem } from "../components/BlogItem"
import { Loading } from "../components/Loading"
import { BASIC_HEADER, API_BLOGS_DELETE, API_PRIVATE_BLOG } from "../constans"
import { getJWT, removeJWT } from "../jwt-token"
import { PATH_BLOGS_NEW, PATH_FORBIDDEN } from "./constants"
import { Blog, ResponseBlogsIndex } from "./response-types"

export function UserProfile() {
    const [blogs, setBlogs] = useState<Blog[]>([])
    const [isLoading, setIsLoading] = useState(true)
    const context: SessionContextType = useContext(SessionContext)
    const navigate = useNavigate()

    const fetchBlogs = async () => {
        const res = await fetch(API_PRIVATE_BLOG, {
            method: "GET",
            headers: getJWT(BASIC_HEADER)
        })

        // JWT token is invalid
        if (res.status === StatusCodes.UNAUTHORIZED) {
            removeJWT()
            return
        }

        const ResBlogs: ResponseBlogsIndex = await res.json()
        setBlogs(ResBlogs)
        setIsLoading(false)
    }

    const onDeleteClick = async (blog: Blog) => {
        const result = window.confirm(`Are you sure you want to delete blog "${blog.title}"?`)
        if (!result)
            return

        const res = await fetch(API_BLOGS_DELETE(blog.id), {
            method: "DELETE",
            headers: getJWT(BASIC_HEADER)
        })

        // JWT token is invalid
        if (res.status === StatusCodes.UNAUTHORIZED) {
            removeJWT()
            return
        }
        if (res.status !== StatusCodes.NO_CONTENT && res.status !== StatusCodes.UNAUTHORIZED)
            return

        setIsLoading(true)
        fetchBlogs()
    }

    useEffect(() => {
        if (context.isLoggedIn === false) {
            navigate(PATH_FORBIDDEN)
            return
        }

        fetchBlogs()
    }, [navigate, context.isLoggedIn])
    return (
        <>
            {(isLoading === true) ? <Loading /> : (
                <div>
                    <h1>Your blogs</h1>
                    <div className="page-options">
                        <Link className="btn" to={PATH_BLOGS_NEW}>New blog</Link>
                    </div>
                    <div className="card-list">
                        {blogs.map((blog: Blog) =>
                            <BlogItem key={blog.id} blog={blog} onDeleteClick={onDeleteClick} />
                        )}
                    </div>
                </div >
            )}
        </>
    )
}