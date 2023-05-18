document.addEventListener("DOMContentLoaded", () => {
    document.querySelector(".logout_button").addEventListener("click", () => {
       document.cookie = "user=;Path=/;Expires=Thu, 01 Jan 1970 00:00:01 GMT;";
       window.location="/login";
    });
    document.querySelector(".edit_button").addEventListener("click", () => {
        window.location="/edit-profile";
    });
});