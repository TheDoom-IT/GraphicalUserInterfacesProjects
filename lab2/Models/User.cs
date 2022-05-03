namespace blog.Models;
using System.ComponentModel.DataAnnotations;

public class User
{
    const int MIN_LOGIN_LENGTH = 5;
    const int MAX_LOGIN_LENGTH = 20;
    const int MIN_PASSWORD_LENGTH = 8;
    const int MAX_PASSWORD_LENGTH = 100;
    const int MAX_EMAIL_LENGTH = 320;
    const int MIN_EMAIL_LENGTH = 3;

    [Key]
    public int Id { get; set; }

    [Required(ErrorMessage = "The field is required")]
    [MinLength(MIN_LOGIN_LENGTH, ErrorMessage = "Login should be at least 5 characters long")]
    [MaxLength(MAX_LOGIN_LENGTH, ErrorMessage = "Login can't be longer than 20 characters")]
    public string Login { get; set; } = null!;

    [Required(ErrorMessage = "The field is required")]
    [MaxLength(MAX_EMAIL_LENGTH)]
    [EmailAddress(ErrorMessage = "Please provide a valid email address")]
    public string Email { get; set; } = null!;

    [Required(ErrorMessage = "The field is required")]
    [MinLength(MIN_PASSWORD_LENGTH, ErrorMessage = "Password should be at least 8 characters long")]
    [MaxLength(MAX_PASSWORD_LENGTH, ErrorMessage = "Password can't be longer than 100 characters")]
    public string Password { get; set; } = null!;
}
