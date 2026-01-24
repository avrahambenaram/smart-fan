export class FanRender {
  #fanManager = null;
  #toggleForm = null;
  #statusText = null;

  constructor(fanManager) {
    this.#fanManager = fanManager;
    this.#toggleForm = document.getElementById('toggle-form');
    this.#statusText = document.getElementById('status-text');

    this.#toggleForm.addEventListener('submit', async e => await this.#onSubmit(e));
  }

  render() {
    if (this.#fanManager.isPowered()) {
      this.#statusText.classList.add('powered');
      this.#statusText.textContent = 'Ligado';
    } else {
      this.#statusText.classList.remove('powered');
      this.#statusText.textContent = 'Desligado';
    }
  }

  async #onSubmit(e) {
    e.preventDefault(); // stop page reload

    try {
      await this.#fanManager.toggle();

      console.log("Fan toggled");
    } catch (err) {
      console.error("Failed to toggle fan", err);
    }
  }
};
