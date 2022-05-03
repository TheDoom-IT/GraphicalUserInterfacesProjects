
document.getElementById("closeDeleteBlogModal").addEventListener('click', () => {
    $('#deleteBlogModal').modal('hide')
})

var buttons = document.getElementsByName("deleteBlogButton")
buttons.forEach((button) => {
    button.addEventListener(
        'click', () => {
            document.getElementById("delete-blog-id").value = button.dataset.id
            document.getElementById("delete-blog-title").innerText = button.dataset.title

            $('#deleteBlogModal').modal('show')
        }
    )
})
