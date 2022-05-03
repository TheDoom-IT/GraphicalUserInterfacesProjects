using blog.Context;
using blog.Services;
using Microsoft.EntityFrameworkCore;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddControllersWithViews();

// Add session
builder.Services.AddDistributedMemoryCache();

builder.Services.AddSession(options =>
{
    options.Cookie.HttpOnly = true;
    options.Cookie.IsEssential = true;
});


// Add dependencies to inject
builder.Services.AddHttpContextAccessor();
var connectionString = builder.Configuration["ConnectionStrings:Default"];
builder.Services.AddDbContextFactory<BlogContext>(options => options.UseSqlite(connectionString));
builder.Services.AddScoped<IUserService, UserService>();
builder.Services.AddScoped<ILoginService, LoginService>();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

app.UseAuthorization();

app.UseSession();

app.MapControllerRoute(
    name: "BlogEntry",
    pattern: "Blog/{BlogId}/BlogEntry/{action}/{id}",
    new { controller = "BlogEntry" }
);

app.MapControllerRoute(
    name: "BlogEntry",
    pattern: "Blog/{BlogId}/BlogEntry/New",
    new { controller = "BlogEntry", action = "New" }
);

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

app.Run();
