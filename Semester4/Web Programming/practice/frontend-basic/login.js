$(() => {
    $(".login-button").on("click", () => {
        let username = $(".username-input").val().trim();
        let password = $(".password-input").val().trim();
        if(username == "" || password == "") {
            $(".error").text("Username and password should not be empty");
            return;
        }
        $.post({
            url: BACKEND_LOGIN_URL,
            data: JSON.stringify({
                username: username,
                password: password
            })
        }).done((result) => {
            CookieUtil.set("user", result['token'], "session", "/", null, null)
            window.location = "main.html";
        }).fail((error) => {
            console.log(error);
            $(".error").text("Invalid username or password");
        })
    })
})