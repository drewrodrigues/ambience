function updateColorsOnClick(color) {
  alert(color);
}

function onDragStart(e) {
  e.dataTransfer.setData("text/plain", e.target.style.backgroundColor);
  e.target.classList.add("dragging");
}

function onDragEnd(e) {
  const blocks = document.querySelectorAll(".block");
  const mouseX = e.clientX;
  const mouseY = e.clientY;

  // Find the block that the mouse is over when the drag ends
  let droppedOverBlock = null;

  let i = 0;
  for (const block of blocks) {
    const rect = block.getBoundingClientRect();

    // Check if the mouse position is within the boundaries of the block
    if (
      mouseX >= rect.left &&
      mouseX <= rect.right &&
      mouseY >= rect.top &&
      mouseY <= rect.bottom
    ) {
      droppedOverBlock = block;
      droppedOverIndex = i;
      break; // Exit the loop once we find the block
    }

    i++;
  }

  if (droppedOverBlock) {
    const draggedColor = e.target.textContent;
    const droppedOverColor = droppedOverBlock.textContent;

    console.log(draggedColor);

    // Make a POST request to update the position
    fetch(`/colors/updatePosition/${draggedColor}/${droppedOverColor}`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
    })
      .then((response) => {
        if (response.ok) {
          // alert(`Successfully moved ${draggedColor} over ${droppedOverColor}`);
          // Optionally reload or update the colors on the page
          window.location.reload(); // Reload the page to see changes
        } else {
          // alert(
          //   `Failed to update position. ${draggedColor} -> ${droppedOverColor}`
          // );
        }
      })
      .catch((error) => {
        console.error("Error:", error);
        alert("An error occurred while updating the position.");
      });
  }
}

const blocks = document.querySelectorAll(".block");
for (const block of blocks) {
  block.addEventListener("dragstart", onDragStart);
  block.addEventListener("dragend", onDragEnd);
}
