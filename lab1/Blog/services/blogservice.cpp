#include "blogservice.h"

BlogService::BlogService(BlogRepository* blogRepository)
{
    this->blogRepository = blogRepository;
    this->currentBlog = nullptr;
}

std::pair<bool, QString> BlogService::createEmptyBlog(QString title, QString userId)
{
    auto blog = blogRepository->findOne(title);
    if(blog.has_value())
        return std::pair(false, tr("Blog with such a title already exists."));

    // create new blog
    if(this->currentBlog == nullptr)
    {
        delete this->currentBlog;
    }

    this->currentBlog = new Blog(title, userId,QList<BlogEntry>());
    this->blogRepository->insertOne(*this->currentBlog);

    return std::pair(true, "");
}

bool BlogService::loadBlogOfUser(QString userId)
{
    auto blog = this->blogRepository->findOneByOwner(userId);
    if(blog.has_value())
    {
        this->currentBlog = new Blog(blog.value());
        return true;
    }

    return false;
}
