export class WifiManager {
  wifis = [];
  #listeners = {
    fetch: [],
    add: [],
    update: [],
  };

  setup() {
    this.#fetchWifi();
    setInterval(() => this.#fetchWifi(), 15000);
    setInterval(() => this.#fetchStatus(), 5000);
  }

  setWifis(wifis) {
    this.wifis = wifis;
    this.#notify('fetch');
  }

  async #fetchWifi() {
    const response = await fetch('/wifi-list');
    if (!response.ok)
      return;
    const data = await response.json();
    if (data.length === 0)
      return;
    this.wifis = data;
    this.#notify('fetch');
  }

  async #fetchStatus() {
    const response = await fetch('/wifi-status');
    if (!response.ok)
      return;
    const data = await response.json();
    if (!data.ssid)
      return;

    const network = this.wifis.find(w => w.ssid === data.ssid);
    if (network.status === data.status)
      return;

    if (network)
      network.status = data.status;
    else
      this.wifis.unshift(data);
    this.#notify('update');
  }

  async connectToWifi(wifiConnectDto) {
    try {
      await this.#_connectToWifi(wifiConnectDto);
      this.#markStatus(wifiConnectDto, 1);
    } catch (err) {
      console.error(err);
      this.#markStatus(wifiConnectDto, 3);
      throw new Error('Erro ao conectar');
    }
  }

  async #_connectToWifi(wifiDto) {
    const response = await fetch('/wifi-setup', {
      method: "POST",
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(wifiDto),
    });
    if (!response.ok)
      throw new Error('Erro ao conectar');
  }

  #markStatus(wifiDto, status) {
    const i = this.wifis.findIndex(w => w.ssid === wifiDto.ssid);
    if (i >= 0) {
      this.wifis[i].status = status;
      this.#notify('update');
      return;
    }

    const wifi = {
      ssid: wifiDto.ssid,
      status: status,
      secure: wifiDto.pass !== '',
    }
    this.wifis.unshift(wifi);
    this.#notify('update');
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
