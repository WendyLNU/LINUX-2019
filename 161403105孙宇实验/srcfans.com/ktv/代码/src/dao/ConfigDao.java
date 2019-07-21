package dao;

import entity.Config;

public class ConfigDao {
	private Config config;
	private static ConfigDao configDao;

	public static ConfigDao instance() {
		if (configDao == null)
			configDao = new ConfigDao();
		return configDao;
	}

	public ConfigDao() {
		config = new Config("Á¿··Ê½KTV", 10, 3, 3);
	}

	public Config getConfig() {
		return config;
	}

	public void setConfig(Config config) {
		this.config = config;
	}
}
