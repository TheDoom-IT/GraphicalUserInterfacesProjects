
//delete blog entry modal
document.getElementById("closeDeleteBlogEntryModal").addEventListener('click', () => {
    $('#deleteBlogEntryModal').modal('hide')
})

var buttons = document.getElementsByName("deleteBlogEntryButton")
buttons.forEach((button) => {
    button.addEventListener(
        'click', () => {
            document.getElementById("delete-blog-entry-blog-id").value = button.dataset.blogId
            document.getElementById("delete-blog-entry-id").value = button.dataset.id
            document.getElementById("delete-blog-entry-title").innerText = button.dataset.title

            $('#deleteBlogEntryModal').modal('show')
        }
    )
})