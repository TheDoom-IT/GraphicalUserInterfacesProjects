namespace blog.Services;

using blog.Context;
using blog.Models;
using Microsoft.EntityFrameworkCore;

public interface ILoginService
{
    public void Register(User user);
    public bool LogIn(User user);
    public void LogOut();
}

public class LoginService : ILoginService
{
    private readonly IDbContextFactory<BlogContext> _blogContextFactory;
    private readonly IUserService _userService;
    private readonly IHttpContextAccessor _httpContextAccessor;


    public LoginService(IDbContextFactory<BlogContext> blogContextFactory, IUserService userService, IHttpContextAccessor httpContextAccessor)
    {
        _blogContextFactory = blogContextFactory;
        _userService = userService;
        _httpContextAccessor = httpContextAccessor;
    }

    public void Register(User user)
    {
        using (var db = _blogContextFactory.CreateDbContext())
        {
            var checkUser = db.Users.Where(u => u.Login == user.Login || u.Email == user.Email).FirstOrDefault();
            if (checkUser != null)
            {
                if (checkUser.Login == user.Login)
                {
                    throw new InvalidLoginException($"Login \"{user.Login}\" is already taken");
                }
                else
                {
                    throw new InvalidEmailException($"Email \"{user.Email}\" is already taken");
                }
            }

            db.Users.Add(user);
            db.SaveChanges();
        }
    }

    public bool LogIn(User user)
    {
        using (var db = _blogContextFactory.CreateDbContext())
        {
            var found = db.Users.Where(u => u.Login == user.Login && u.Password == user.Password).FirstOrDefault();
            if (found == null)
                return false;

            _httpContextAccessor.HttpContext?.Session.SetInt32(UserService.SessionKeyCurrentUserId, found.Id);
            return true;
        }
    }
    public void LogOut()
    {
        _userService.LogOut();
    }
}

public class InvalidLoginException : Exception
{
    public InvalidLoginException() { }

    public InvalidLoginException(string message) : base(message) { }

    public InvalidLoginException(string message, Exception inner) : base(message, inner) { }
}

public class InvalidEmailException : Exception
{
    public InvalidEmailException() { }

    public InvalidEmailException(string message) : base(message) { }

    public InvalidEmailException(string message, Exception inner) : base(message, inner) { }
}

public class InvalidPasswordException : Exception
{
    public InvalidPasswordException() { }

    public InvalidPasswordException(string message) : base(message) { }

    public InvalidPasswordException(string message, Exception inner) : base(message, inner) { }
}