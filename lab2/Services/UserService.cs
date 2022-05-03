namespace blog.Services;

using blog.Context;
using blog.Models;
using Microsoft.EntityFrameworkCore;

public interface IUserService
{
    public void LogOut();

    public User? CurrentUser();
    public bool IsLoggedIn();
}

public class UserService : IUserService
{
    public const string SessionKeyCurrentUserId = "CurrentUserId";
    private readonly IHttpContextAccessor _httpContextAccessor;
    private readonly IDbContextFactory<BlogContext> _blogContextFactory;
    public UserService(IHttpContextAccessor httpContextAccessor, IDbContextFactory<BlogContext> blogContextFactory)
    {
        _httpContextAccessor = httpContextAccessor;
        _blogContextFactory = blogContextFactory;
    }

    private User? _currentUser;

    public User? CurrentUser()
    {
        if (_currentUser != null)
            return _currentUser;
        _currentUser = getUserFromSession();
        return _currentUser;
    }

    public void LogOut()
    {
        _httpContextAccessor.HttpContext?.Session.Clear();
        _currentUser = null;
    }

    public bool IsLoggedIn()
    {
        if (CurrentUser() == null)
            return false;

        return true;
    }

    private User? getUserFromSession()
    {
        var userId = _httpContextAccessor.HttpContext?.Session.GetInt32(SessionKeyCurrentUserId);
        if (userId == null)
            return null;

        using (var db = _blogContextFactory.CreateDbContext())
        {
            return db.Users.Find(userId);
        }
    }
}