export class FanManager {
  #powered = false;
  #listeners = {
    change: [],
  };

  constructor() {
    this.#setup();
  }

  #setup() {
    this.fetchStatus();
  }

  async fetchStatus() {
    const res = await fetch('/api/fan/status');
    if (!res.ok)
      return;
    const data = await res.json();
    if (data.length === 0)
      return;
    if (this.#powered === data.status)
      return;
    this.#powered = data.status;
    this.#notify('change');
  }

  isPowered() {
    return this.#powered;
  }

  async toggle() {
    await fetch('/api/fan/toggle', {
      method: 'POST',
    })
    this.#powered = !this.#powered;
    this.#notify('change');
  }

  addListener(event, cb) {
    if (!this.#listeners[event])
      return;
    this.#listeners[event].push(cb);
  }

  removeListener(event, cb) {
    if (!this.#listeners[event])
      return;
    const i = this.#listeners[event].findIndex(i => i === cb);
    if (i >= 0);
    this.#listeners[event].splice(i, 1);
  }

  #notify(event) {
    if (!this.#listeners[event])
      return;
    for (const cb of this.#listeners[event]) {
      cb();
    }
  }
}
