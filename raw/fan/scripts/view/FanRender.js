export class FanRender {
  #fanManager = null;
  #toggleForm = null;
  #statusText = null;
  #submiting = false;

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
    try {
      await this.#_onSubmit(e);
    } catch (err) {
      console.error("Failed to toggle fan", err);
    } finally {
      this.#submiting = false;
    }
  }

  async #_onSubmit(e) {
    e.preventDefault();
    if (this.#submiting)
      return;
    this.#submiting = true;
    await this.#fanManager.toggle();
  }
};
