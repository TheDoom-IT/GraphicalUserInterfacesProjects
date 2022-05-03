namespace blog.Context;

using Microsoft.EntityFrameworkCore;
using blog.Models;

public class BlogContext : DbContext
{
    public DbSet<Blog> Blogs => Set<Blog>();
    public DbSet<BlogEntry> BlogEntries => Set<BlogEntry>();
    public DbSet<User> Users => Set<User>();

    public BlogContext(DbContextOptions<BlogContext> options) : base(options)
    {
    }
}
