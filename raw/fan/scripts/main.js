import { FanManager } from "./manager/FanManager.js";
import { FanRender } from "./view/FanRender.js";

document.addEventListener('DOMContentLoaded', () => {
  const fanManager = new FanManager();
  const fanRender = new FanRender(fanManager);
  fanManager.addListener('change', () => fanRender.render());
  fanRender.render();
})
