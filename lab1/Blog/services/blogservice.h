#ifndef BLOGSERVICE_H
#define BLOGSERVICE_H

#include <QtCore>
#include <utility>
#include "models/blog.h"
#include "repositories/blogrepository.h"
#include "models/user.h"

class BlogService
{
    Q_DECLARE_TR_FUNCTIONS(BlogService)

public:
    BlogService(BlogRepository*);

    std::pair<bool, QString> createEmptyBlog(QString title, QString userId);
    bool loadBlogOfUser(QString userId);

    Blog* getCurrentBlog() const {
        return currentBlog;
    }

    void removeEntries(QList<int>);
    void updateEntry(int, QString, QString);
    void addEntry(QString, QString);
//public signals:
//    void blogUpdated();

private:
    Blog* currentBlog;
    BlogRepository* blogRepository;
};
#endif // BLOGSERVICE_H
