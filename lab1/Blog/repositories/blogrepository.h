#ifndef BLOGREPOSITORY_H
#define BLOGREPOSITORY_H

#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <optional>
#include "../models/blog.h"

class BlogRepository
{
    Q_DECLARE_TR_FUNCTIONS(LoginService)
public:
    BlogRepository(QString dataPath, QString blogsDir);
    ~BlogRepository();

    std::optional<Blog> findOneByOwner(QString ownerId) const;
    std::optional<Blog> findOne(QString blogId) const;
    std::pair<bool, QString> insertOne(const Blog&) const;
    std::pair<bool, QString> updateOne(const Blog&) const;

private:
    QDir dataDir;
};

#endif // BLOGREPOSITORY_H
