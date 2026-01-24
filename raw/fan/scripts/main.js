document.addEventListener('DOMContentLoaded', () => {
  const form = document.getElementById('toggle-form');
  form.addEventListener("submit", async (e) => {
    e.preventDefault(); // stop page reload

    try {
      await fetch(form.action, {
        method: "POST",
      });

      // optional UI feedback
      console.log("Fan toggled");
    } catch (err) {
      console.error("Failed to toggle fan", err);
    }
  });
})
