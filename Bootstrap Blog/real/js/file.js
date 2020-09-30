// let counter = 0;
document.addEventListener("DOMContentLoaded", (e) => {
    if (localStorage.getItem("access") === null) {
        document.querySelector("#submit").addEventListener("click", (e) => {
            localStorage.setItem("access", "1");
        })
    } else if (localStorage.getItem("access") === "1") {
        console.log("success");
        localStorage.removeItem("access");
        alert("the form you just submitted was a fake form... click on the precautions button for  more details");
        add_button()
    }

    function add_button() {
        let div = document.createElement("div");
        div.innerHTML = `<form action="http://localhost:3400/admin-original" method="GET">
        <button type="submit" class="btn btn-success mt-2 float-right">Precautions</button> 
        </form>`
        document.querySelector("#form").appendChild(div).insertBefore("#submit");
    }

})