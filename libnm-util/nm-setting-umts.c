/* -*- Mode: C; tab-width: 5; indent-tabs-mode: t; c-basic-offset: 5 -*- */

#include <string.h>
#include "nm-setting-umts.h"
#include "nm-utils.h"

G_DEFINE_TYPE (NMSettingUmts, nm_setting_umts, NM_TYPE_SETTING)

enum {
	PROP_0,
	PROP_NUMBER,
	PROP_USERNAME,
	PROP_PASSWORD,
	PROP_APN,
	PROP_NETWORK_ID,
	PROP_NETWORK_TYPE,
	PROP_BAND,
	PROP_PIN,
	PROP_PUK,

	LAST_PROP
};

NMSetting *
nm_setting_umts_new (void)
{
	return (NMSetting *) g_object_new (NM_TYPE_SETTING_UMTS, NULL);
}

static gboolean
verify (NMSetting *setting, GSList *all_settings)
{
	NMSettingUmts *self = NM_SETTING_UMTS (setting);

	if (!self->number || strlen (self->number) < 1) {
		nm_warning ("Missing phone number");
		return FALSE;
	}

	return TRUE;
}

static void
nm_setting_umts_init (NMSettingUmts *setting)
{
	((NMSetting *) setting)->name = g_strdup (NM_SETTING_UMTS_SETTING_NAME);
}

static void
finalize (GObject *object)
{
	NMSettingUmts *self = NM_SETTING_UMTS (object);

	g_free (self->number);
	g_free (self->username);
	g_free (self->password);
	g_free (self->apn);
	g_free (self->network_id);
	g_free (self->pin);
	g_free (self->puk);

	G_OBJECT_CLASS (nm_setting_umts_parent_class)->finalize (object);
}

static void
set_property (GObject *object, guint prop_id,
		    const GValue *value, GParamSpec *pspec)
{
	NMSettingUmts *setting = NM_SETTING_UMTS (object);

	switch (prop_id) {
	case PROP_NUMBER:
		g_free (setting->number);
		setting->number = g_value_dup_string (value);
		break;
	case PROP_USERNAME:
		g_free (setting->username);
		setting->username = g_value_dup_string (value);
		break;
	case PROP_PASSWORD:
		g_free (setting->password);
		setting->password = g_value_dup_string (value);
		break;
	case PROP_APN:
		g_free (setting->apn);
		setting->apn = g_value_dup_string (value);
		break;
	case PROP_NETWORK_ID:
		g_free (setting->network_id);
		setting->network_id = g_value_dup_string (value);
		break;
	case PROP_NETWORK_TYPE:
		setting->network_type = g_value_get_int (value);
		break;
	case PROP_BAND:
		setting->band = g_value_get_int (value);
		break;
	case PROP_PIN:
		g_free (setting->pin);
		setting->pin = g_value_dup_string (value);
		break;
	case PROP_PUK:
		g_free (setting->puk);
		setting->puk = g_value_dup_string (value);
		break;	
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
get_property (GObject *object, guint prop_id,
		    GValue *value, GParamSpec *pspec)
{
	NMSettingUmts *setting = NM_SETTING_UMTS (object);

	switch (prop_id) {
	case PROP_NUMBER:
		g_value_set_string (value, setting->number);
		break;
	case PROP_USERNAME:
		g_value_set_string (value, setting->username);
		break;
	case PROP_PASSWORD:
		g_value_set_string (value, setting->password);
		break;
	case PROP_APN:
		g_value_set_string (value, setting->apn);
		break;
	case PROP_NETWORK_ID:
		g_value_set_string (value, setting->network_id);
		break;
	case PROP_NETWORK_TYPE:
		g_value_set_int (value, setting->network_type);
		break;
	case PROP_BAND:
		g_value_set_int (value, setting->band);
		break;
	case PROP_PIN:
		g_value_set_string (value, setting->pin);
		break;
	case PROP_PUK:
		g_value_set_string (value, setting->puk);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
nm_setting_umts_class_init (NMSettingUmtsClass *setting_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (setting_class);
	NMSettingClass *parent_class = NM_SETTING_CLASS (setting_class);

	/* virtual methods */
	object_class->set_property = set_property;
	object_class->get_property = get_property;
	object_class->finalize     = finalize;
	parent_class->verify       = verify;

	/* Properties */
	g_object_class_install_property
		(object_class, PROP_NUMBER,
		 g_param_spec_string (NM_SETTING_UMTS_NUMBER,
						  "Number",
						  "Number",
						  NULL,
						  G_PARAM_READWRITE | NM_SETTING_PARAM_SERIALIZE));

	g_object_class_install_property
		(object_class, PROP_USERNAME,
		 g_param_spec_string (NM_SETTING_UMTS_USERNAME,
						  "Username",
						  "Username",
						  NULL,
						  G_PARAM_READWRITE | NM_SETTING_PARAM_SERIALIZE));

	g_object_class_install_property
		(object_class, PROP_PASSWORD,
		 g_param_spec_string (NM_SETTING_UMTS_PASSWORD,
						  "Password",
						  "Password",
						  NULL,
						  G_PARAM_READWRITE | NM_SETTING_PARAM_SERIALIZE | NM_SETTING_PARAM_SECRET));

	g_object_class_install_property
		(object_class, PROP_APN,
		 g_param_spec_string (NM_SETTING_UMTS_APN,
						  "APN",
						  "APN",
						  NULL,
						  G_PARAM_READWRITE | NM_SETTING_PARAM_SERIALIZE));

	g_object_class_install_property
		(object_class, PROP_NETWORK_ID,
		 g_param_spec_string (NM_SETTING_UMTS_NETWORK_ID,
						  "Network ID",
						  "Network ID",
						  NULL,
						  G_PARAM_READWRITE | NM_SETTING_PARAM_SERIALIZE));

	g_object_class_install_property
		(object_class, PROP_NETWORK_TYPE,
		 g_param_spec_int (NM_SETTING_UMTS_NETWORK_TYPE,
					    "Network type",
					    "Network type",
					    NM_UMTS_NETWORK_ANY,
					    NM_UMTS_NETWORK_PREFER_UMTS,
					    NM_UMTS_NETWORK_ANY,
					    G_PARAM_READWRITE | NM_SETTING_PARAM_SERIALIZE));

	g_object_class_install_property
		(object_class, PROP_BAND,
		 g_param_spec_int (NM_SETTING_UMTS_BAND,
					    "Band",
					    "Band",
					    -1, 5, -1, /* FIXME: Use an enum for it */
					    G_PARAM_READWRITE | NM_SETTING_PARAM_SERIALIZE));

	g_object_class_install_property
		(object_class, PROP_PIN,
		 g_param_spec_string (NM_SETTING_UMTS_PIN,
						  "PIN",
						  "PIN",
						  NULL,
						  G_PARAM_READWRITE | NM_SETTING_PARAM_SERIALIZE | NM_SETTING_PARAM_SECRET));

	g_object_class_install_property
		(object_class, PROP_PUK,
		 g_param_spec_string (NM_SETTING_UMTS_PUK,
						  "PUK",
						  "PUK",
						  NULL,
						  G_PARAM_READWRITE | NM_SETTING_PARAM_SERIALIZE | NM_SETTING_PARAM_SECRET));
}
