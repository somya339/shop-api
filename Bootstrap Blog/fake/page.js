const express = require("express");
const app = express();
const path = require("path");
const parser = require("body-parser");
app.use(parser.urlencoded({
    extended: true
}));
app.use("/admin", express.static(path.join(__dirname, '../', 'Bootstrap Blog')));
app.post("/admin-original", express.static(path.join(__dirname, '../', 'Bootstrap Blog')));
app.get("/admin-original",(req,res,next)=>
{
    res.sendFile(path.join(__dirname,"index2.html"));
})
app.listen(3400);
