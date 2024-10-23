const express = require("express");
const bodyParser = require("body-parser");
const fs = require("fs");
const app = express();
const PORT = 3000;

app.use(bodyParser.json());
app.use(express.static("public"));
app.set("view engine", "pug");

app.get("/colors", (_, res) => {
  const colors = JSON.parse(
    fs.readFileSync("colors.json", { encoding: "utf-8" })
  );
  res.render("color", { colors });
});

app.post("/colors/:color", (req, res) => {
  const colorsFile = JSON.parse(
    fs.readFileSync("colors.json", { encoding: "utf-8" })
  );
  const color = req.params.color;

  if (colorsFile.yes.includes(color)) {
    // place into no
    colorsFile.yes = colorsFile.yes.filter(
      (colorInYes) => colorInYes !== color
    );
    colorsFile.no.push(color);
  } else {
    // place into yes
    colorsFile.no = colorsFile.no.filter((colorInYes) => colorInYes !== color);
    colorsFile.yes.push(color);
  }

  fs.writeFileSync("colors.json", JSON.stringify(colorsFile));
  res.redirect("/colors");
});

app.post("/colors/updatePosition/:from/:to", (req, res) => {
  const colorsFile = JSON.parse(
    fs.readFileSync("colors.json", { encoding: "utf-8" })
  );
  const { from, to } = req.params;

  // Find the color in the 'yes' array
  const fromIndex = colorsFile.yes.indexOf(from);
  const toIndex = colorsFile.yes.indexOf(to);

  // If the color is found in 'yes', move it within that array
  if (fromIndex !== -1 && toIndex !== -1) {
    const colorToMove = colorsFile.yes.splice(fromIndex, 1)[0];
    colorsFile.yes.splice(toIndex, 0, colorToMove);
  }

  // If the color is found in 'no', do the same
  const fromIndexNo = colorsFile.no.indexOf(from);
  const toIndexNo = colorsFile.no.indexOf(to);

  if (fromIndexNo !== -1 && toIndexNo !== -1) {
    const colorToMove = colorsFile.no.splice(fromIndexNo, 1)[0];
    colorsFile.no.splice(toIndexNo, 0, colorToMove);
  }

  // Write the updated colors back to the file
  fs.writeFileSync("colors.json", JSON.stringify(colorsFile));
  res.redirect("/colors");
});

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
