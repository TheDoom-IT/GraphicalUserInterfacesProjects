using Microsoft.AspNetCore.Mvc;
using blog.Context;
using blog.Services;
using blog.Models;
using Microsoft.EntityFrameworkCore;

namespace blog.Controllers;

public class BaseController : Controller
{
    protected readonly ILogger<BaseController> _logger;
    protected readonly IDbContextFactory<BlogContext> _blogContextFactory;
    protected readonly IUserService _userService;

    public BaseController(ILogger<BaseController> logger, IDbContextFactory<BlogContext> blogContextFactory, IUserService userService)
    {
        _logger = logger;
        _blogContextFactory = blogContextFactory;
        _userService = userService;
    }

    protected int? CurrentUserId
    {
        get
        {
            return CurrentUser?.Id;
        }
    }

    protected User? CurrentUser
    {
        get
        {
            return _userService.CurrentUser();
        }
    }
}
