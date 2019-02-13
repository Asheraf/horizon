/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

/* This is an auto-generated file, please do not edit manually. */

#include "PacketHandlerFactory.hpp"
#include "Server/Common/Models/Configuration/GeneralServerConfiguration.hpp"
#include "Server/Zone/Zone.hpp"

#include "Server/Zone/Packets/Ragexe/Packets.hpp"
#include "Server/Zone/Packets/RE/Packets.hpp"
#include "Server/Zone/Packets/Zero/Packets.hpp"
#include "Server/Zone/Packets/Ragexe/20170104/PacketsRagexe20170104.hpp"
#include "Server/Zone/Packets/Ragexe/20170104/PacketHandlerRagexe20170104.hpp"
#include "Server/Zone/Packets/RE/20170104/PacketsRE20170104.hpp"
#include "Server/Zone/Packets/RE/20170104/PacketHandlerRE20170104.hpp"
#include "Server/Zone/Packets/Ragexe/20170111/PacketsRagexe20170111.hpp"
#include "Server/Zone/Packets/Ragexe/20170111/PacketHandlerRagexe20170111.hpp"
#include "Server/Zone/Packets/RE/20170111/PacketsRE20170111.hpp"
#include "Server/Zone/Packets/RE/20170111/PacketHandlerRE20170111.hpp"
#include "Server/Zone/Packets/Ragexe/20170118/PacketsRagexe20170118.hpp"
#include "Server/Zone/Packets/Ragexe/20170118/PacketHandlerRagexe20170118.hpp"
#include "Server/Zone/Packets/RE/20170118/PacketsRE20170118.hpp"
#include "Server/Zone/Packets/RE/20170118/PacketHandlerRE20170118.hpp"
#include "Server/Zone/Packets/Ragexe/20170125/PacketsRagexe20170125.hpp"
#include "Server/Zone/Packets/Ragexe/20170125/PacketHandlerRagexe20170125.hpp"
#include "Server/Zone/Packets/RE/20170125/PacketsRE20170125.hpp"
#include "Server/Zone/Packets/RE/20170125/PacketHandlerRE20170125.hpp"
#include "Server/Zone/Packets/Ragexe/20170201/PacketsRagexe20170201.hpp"
#include "Server/Zone/Packets/Ragexe/20170201/PacketHandlerRagexe20170201.hpp"
#include "Server/Zone/Packets/RE/20170201/PacketsRE20170201.hpp"
#include "Server/Zone/Packets/RE/20170201/PacketHandlerRE20170201.hpp"
#include "Server/Zone/Packets/Ragexe/20170208/PacketsRagexe20170208.hpp"
#include "Server/Zone/Packets/Ragexe/20170208/PacketHandlerRagexe20170208.hpp"
#include "Server/Zone/Packets/RE/20170208/PacketsRE20170208.hpp"
#include "Server/Zone/Packets/RE/20170208/PacketHandlerRE20170208.hpp"
#include "Server/Zone/Packets/Ragexe/20170215/PacketsRagexe20170215.hpp"
#include "Server/Zone/Packets/Ragexe/20170215/PacketHandlerRagexe20170215.hpp"
#include "Server/Zone/Packets/RE/20170215/PacketsRE20170215.hpp"
#include "Server/Zone/Packets/RE/20170215/PacketHandlerRE20170215.hpp"
#include "Server/Zone/Packets/Ragexe/20170222/PacketsRagexe20170222.hpp"
#include "Server/Zone/Packets/Ragexe/20170222/PacketHandlerRagexe20170222.hpp"
#include "Server/Zone/Packets/RE/20170222/PacketsRE20170222.hpp"
#include "Server/Zone/Packets/RE/20170222/PacketHandlerRE20170222.hpp"
#include "Server/Zone/Packets/Ragexe/20170228/PacketsRagexe20170228.hpp"
#include "Server/Zone/Packets/Ragexe/20170228/PacketHandlerRagexe20170228.hpp"
#include "Server/Zone/Packets/RE/20170228/PacketsRE20170228.hpp"
#include "Server/Zone/Packets/RE/20170228/PacketHandlerRE20170228.hpp"
#include "Server/Zone/Packets/Ragexe/20170308/PacketsRagexe20170308.hpp"
#include "Server/Zone/Packets/Ragexe/20170308/PacketHandlerRagexe20170308.hpp"
#include "Server/Zone/Packets/RE/20170308/PacketsRE20170308.hpp"
#include "Server/Zone/Packets/RE/20170308/PacketHandlerRE20170308.hpp"
#include "Server/Zone/Packets/Ragexe/20170315/PacketsRagexe20170315.hpp"
#include "Server/Zone/Packets/Ragexe/20170315/PacketHandlerRagexe20170315.hpp"
#include "Server/Zone/Packets/RE/20170315/PacketsRE20170315.hpp"
#include "Server/Zone/Packets/RE/20170315/PacketHandlerRE20170315.hpp"
#include "Server/Zone/Packets/Ragexe/20170322/PacketsRagexe20170322.hpp"
#include "Server/Zone/Packets/Ragexe/20170322/PacketHandlerRagexe20170322.hpp"
#include "Server/Zone/Packets/RE/20170322/PacketsRE20170322.hpp"
#include "Server/Zone/Packets/RE/20170322/PacketHandlerRE20170322.hpp"
#include "Server/Zone/Packets/Ragexe/20170329/PacketsRagexe20170329.hpp"
#include "Server/Zone/Packets/Ragexe/20170329/PacketHandlerRagexe20170329.hpp"
#include "Server/Zone/Packets/RE/20170329/PacketsRE20170329.hpp"
#include "Server/Zone/Packets/RE/20170329/PacketHandlerRE20170329.hpp"
#include "Server/Zone/Packets/Ragexe/20170405/PacketsRagexe20170405.hpp"
#include "Server/Zone/Packets/Ragexe/20170405/PacketHandlerRagexe20170405.hpp"
#include "Server/Zone/Packets/RE/20170405/PacketsRE20170405.hpp"
#include "Server/Zone/Packets/RE/20170405/PacketHandlerRE20170405.hpp"
#include "Server/Zone/Packets/Ragexe/20170412/PacketsRagexe20170412.hpp"
#include "Server/Zone/Packets/Ragexe/20170412/PacketHandlerRagexe20170412.hpp"
#include "Server/Zone/Packets/RE/20170412/PacketsRE20170412.hpp"
#include "Server/Zone/Packets/RE/20170412/PacketHandlerRE20170412.hpp"
#include "Server/Zone/Packets/Ragexe/20170419/PacketsRagexe20170419.hpp"
#include "Server/Zone/Packets/Ragexe/20170419/PacketHandlerRagexe20170419.hpp"
#include "Server/Zone/Packets/RE/20170419/PacketsRE20170419.hpp"
#include "Server/Zone/Packets/RE/20170419/PacketHandlerRE20170419.hpp"
#include "Server/Zone/Packets/Ragexe/20170426/PacketsRagexe20170426.hpp"
#include "Server/Zone/Packets/Ragexe/20170426/PacketHandlerRagexe20170426.hpp"
#include "Server/Zone/Packets/RE/20170426/PacketsRE20170426.hpp"
#include "Server/Zone/Packets/RE/20170426/PacketHandlerRE20170426.hpp"
#include "Server/Zone/Packets/Ragexe/20170502/PacketsRagexe20170502.hpp"
#include "Server/Zone/Packets/Ragexe/20170502/PacketHandlerRagexe20170502.hpp"
#include "Server/Zone/Packets/RE/20170502/PacketsRE20170502.hpp"
#include "Server/Zone/Packets/RE/20170502/PacketHandlerRE20170502.hpp"
#include "Server/Zone/Packets/Ragexe/20170517/PacketsRagexe20170517.hpp"
#include "Server/Zone/Packets/Ragexe/20170517/PacketHandlerRagexe20170517.hpp"
#include "Server/Zone/Packets/RE/20170517/PacketsRE20170517.hpp"
#include "Server/Zone/Packets/RE/20170517/PacketHandlerRE20170517.hpp"
#include "Server/Zone/Packets/Ragexe/20170524/PacketsRagexe20170524.hpp"
#include "Server/Zone/Packets/Ragexe/20170524/PacketHandlerRagexe20170524.hpp"
#include "Server/Zone/Packets/RE/20170524/PacketsRE20170524.hpp"
#include "Server/Zone/Packets/RE/20170524/PacketHandlerRE20170524.hpp"
#include "Server/Zone/Packets/Ragexe/20170531/PacketsRagexe20170531.hpp"
#include "Server/Zone/Packets/Ragexe/20170531/PacketHandlerRagexe20170531.hpp"
#include "Server/Zone/Packets/RE/20170531/PacketsRE20170531.hpp"
#include "Server/Zone/Packets/RE/20170531/PacketHandlerRE20170531.hpp"
#include "Server/Zone/Packets/Ragexe/20170607/PacketsRagexe20170607.hpp"
#include "Server/Zone/Packets/Ragexe/20170607/PacketHandlerRagexe20170607.hpp"
#include "Server/Zone/Packets/RE/20170607/PacketsRE20170607.hpp"
#include "Server/Zone/Packets/RE/20170607/PacketHandlerRE20170607.hpp"
#include "Server/Zone/Packets/Ragexe/20170614/PacketsRagexe20170614.hpp"
#include "Server/Zone/Packets/Ragexe/20170614/PacketHandlerRagexe20170614.hpp"
#include "Server/Zone/Packets/RE/20170614/PacketsRE20170614.hpp"
#include "Server/Zone/Packets/RE/20170614/PacketHandlerRE20170614.hpp"
#include "Server/Zone/Packets/Ragexe/20170621/PacketsRagexe20170621.hpp"
#include "Server/Zone/Packets/Ragexe/20170621/PacketHandlerRagexe20170621.hpp"
#include "Server/Zone/Packets/RE/20170621/PacketsRE20170621.hpp"
#include "Server/Zone/Packets/RE/20170621/PacketHandlerRE20170621.hpp"
#include "Server/Zone/Packets/Ragexe/20170628/PacketsRagexe20170628.hpp"
#include "Server/Zone/Packets/Ragexe/20170628/PacketHandlerRagexe20170628.hpp"
#include "Server/Zone/Packets/RE/20170628/PacketsRE20170628.hpp"
#include "Server/Zone/Packets/RE/20170628/PacketHandlerRE20170628.hpp"
#include "Server/Zone/Packets/Ragexe/20170705/PacketsRagexe20170705.hpp"
#include "Server/Zone/Packets/Ragexe/20170705/PacketHandlerRagexe20170705.hpp"
#include "Server/Zone/Packets/RE/20170705/PacketsRE20170705.hpp"
#include "Server/Zone/Packets/RE/20170705/PacketHandlerRE20170705.hpp"
#include "Server/Zone/Packets/Ragexe/20170712/PacketsRagexe20170712.hpp"
#include "Server/Zone/Packets/Ragexe/20170712/PacketHandlerRagexe20170712.hpp"
#include "Server/Zone/Packets/RE/20170712/PacketsRE20170712.hpp"
#include "Server/Zone/Packets/RE/20170712/PacketHandlerRE20170712.hpp"
#include "Server/Zone/Packets/Ragexe/20170719/PacketsRagexe20170719.hpp"
#include "Server/Zone/Packets/Ragexe/20170719/PacketHandlerRagexe20170719.hpp"
#include "Server/Zone/Packets/RE/20170719/PacketsRE20170719.hpp"
#include "Server/Zone/Packets/RE/20170719/PacketHandlerRE20170719.hpp"
#include "Server/Zone/Packets/Ragexe/20170726/PacketsRagexe20170726.hpp"
#include "Server/Zone/Packets/Ragexe/20170726/PacketHandlerRagexe20170726.hpp"
#include "Server/Zone/Packets/RE/20170726/PacketsRE20170726.hpp"
#include "Server/Zone/Packets/RE/20170726/PacketHandlerRE20170726.hpp"
#include "Server/Zone/Packets/Ragexe/20170801/PacketsRagexe20170801.hpp"
#include "Server/Zone/Packets/Ragexe/20170801/PacketHandlerRagexe20170801.hpp"
#include "Server/Zone/Packets/RE/20170801/PacketsRE20170801.hpp"
#include "Server/Zone/Packets/RE/20170801/PacketHandlerRE20170801.hpp"
#include "Server/Zone/Packets/Ragexe/20170809/PacketsRagexe20170809.hpp"
#include "Server/Zone/Packets/Ragexe/20170809/PacketHandlerRagexe20170809.hpp"
#include "Server/Zone/Packets/RE/20170809/PacketsRE20170809.hpp"
#include "Server/Zone/Packets/RE/20170809/PacketHandlerRE20170809.hpp"
#include "Server/Zone/Packets/Ragexe/20170816/PacketsRagexe20170816.hpp"
#include "Server/Zone/Packets/Ragexe/20170816/PacketHandlerRagexe20170816.hpp"
#include "Server/Zone/Packets/RE/20170816/PacketsRE20170816.hpp"
#include "Server/Zone/Packets/RE/20170816/PacketHandlerRE20170816.hpp"
#include "Server/Zone/Packets/Ragexe/20170823/PacketsRagexe20170823.hpp"
#include "Server/Zone/Packets/Ragexe/20170823/PacketHandlerRagexe20170823.hpp"
#include "Server/Zone/Packets/RE/20170823/PacketsRE20170823.hpp"
#include "Server/Zone/Packets/RE/20170823/PacketHandlerRE20170823.hpp"
#include "Server/Zone/Packets/Ragexe/20170830/PacketsRagexe20170830.hpp"
#include "Server/Zone/Packets/Ragexe/20170830/PacketHandlerRagexe20170830.hpp"
#include "Server/Zone/Packets/RE/20170830/PacketsRE20170830.hpp"
#include "Server/Zone/Packets/RE/20170830/PacketHandlerRE20170830.hpp"
#include "Server/Zone/Packets/Ragexe/20170906/PacketsRagexe20170906.hpp"
#include "Server/Zone/Packets/Ragexe/20170906/PacketHandlerRagexe20170906.hpp"
#include "Server/Zone/Packets/RE/20170906/PacketsRE20170906.hpp"
#include "Server/Zone/Packets/RE/20170906/PacketHandlerRE20170906.hpp"
#include "Server/Zone/Packets/Ragexe/20170913/PacketsRagexe20170913.hpp"
#include "Server/Zone/Packets/Ragexe/20170913/PacketHandlerRagexe20170913.hpp"
#include "Server/Zone/Packets/RE/20170913/PacketsRE20170913.hpp"
#include "Server/Zone/Packets/RE/20170913/PacketHandlerRE20170913.hpp"
#include "Server/Zone/Packets/Ragexe/20170920/PacketsRagexe20170920.hpp"
#include "Server/Zone/Packets/Ragexe/20170920/PacketHandlerRagexe20170920.hpp"
#include "Server/Zone/Packets/RE/20170920/PacketsRE20170920.hpp"
#include "Server/Zone/Packets/RE/20170920/PacketHandlerRE20170920.hpp"
#include "Server/Zone/Packets/Ragexe/20170927/PacketsRagexe20170927.hpp"
#include "Server/Zone/Packets/Ragexe/20170927/PacketHandlerRagexe20170927.hpp"
#include "Server/Zone/Packets/RE/20170927/PacketsRE20170927.hpp"
#include "Server/Zone/Packets/RE/20170927/PacketHandlerRE20170927.hpp"
#include "Server/Zone/Packets/Ragexe/20171002/PacketsRagexe20171002.hpp"
#include "Server/Zone/Packets/Ragexe/20171002/PacketHandlerRagexe20171002.hpp"
#include "Server/Zone/Packets/RE/20171002/PacketsRE20171002.hpp"
#include "Server/Zone/Packets/RE/20171002/PacketHandlerRE20171002.hpp"
#include "Server/Zone/Packets/Ragexe/20171011/PacketsRagexe20171011.hpp"
#include "Server/Zone/Packets/Ragexe/20171011/PacketHandlerRagexe20171011.hpp"
#include "Server/Zone/Packets/RE/20171011/PacketsRE20171011.hpp"
#include "Server/Zone/Packets/RE/20171011/PacketHandlerRE20171011.hpp"
#include "Server/Zone/Packets/Ragexe/20171018/PacketsRagexe20171018.hpp"
#include "Server/Zone/Packets/Ragexe/20171018/PacketHandlerRagexe20171018.hpp"
#include "Server/Zone/Packets/RE/20171018/PacketsRE20171018.hpp"
#include "Server/Zone/Packets/RE/20171018/PacketHandlerRE20171018.hpp"
#include "Server/Zone/Packets/Zero/20171018/PacketsZero20171018.hpp"
#include "Server/Zone/Packets/Zero/20171018/PacketHandlerZero20171018.hpp"
#include "Server/Zone/Packets/Zero/20171019/PacketsZero20171019.hpp"
#include "Server/Zone/Packets/Zero/20171019/PacketHandlerZero20171019.hpp"
#include "Server/Zone/Packets/Zero/20171023/PacketsZero20171023.hpp"
#include "Server/Zone/Packets/Zero/20171023/PacketHandlerZero20171023.hpp"
#include "Server/Zone/Packets/Zero/20171024/PacketsZero20171024.hpp"
#include "Server/Zone/Packets/Zero/20171024/PacketHandlerZero20171024.hpp"
#include "Server/Zone/Packets/Ragexe/20171025/PacketsRagexe20171025.hpp"
#include "Server/Zone/Packets/Ragexe/20171025/PacketHandlerRagexe20171025.hpp"
#include "Server/Zone/Packets/RE/20171025/PacketsRE20171025.hpp"
#include "Server/Zone/Packets/RE/20171025/PacketHandlerRE20171025.hpp"
#include "Server/Zone/Packets/Zero/20171025/PacketsZero20171025.hpp"
#include "Server/Zone/Packets/Zero/20171025/PacketHandlerZero20171025.hpp"
#include "Server/Zone/Packets/Zero/20171027/PacketsZero20171027.hpp"
#include "Server/Zone/Packets/Zero/20171027/PacketHandlerZero20171027.hpp"
#include "Server/Zone/Packets/Zero/20171030/PacketsZero20171030.hpp"
#include "Server/Zone/Packets/Zero/20171030/PacketHandlerZero20171030.hpp"
#include "Server/Zone/Packets/Zero/20171031/PacketsZero20171031.hpp"
#include "Server/Zone/Packets/Zero/20171031/PacketHandlerZero20171031.hpp"
#include "Server/Zone/Packets/Ragexe/20171101/PacketsRagexe20171101.hpp"
#include "Server/Zone/Packets/Ragexe/20171101/PacketHandlerRagexe20171101.hpp"
#include "Server/Zone/Packets/RE/20171101/PacketsRE20171101.hpp"
#include "Server/Zone/Packets/RE/20171101/PacketHandlerRE20171101.hpp"
#include "Server/Zone/Packets/Ragexe/20171108/PacketsRagexe20171108.hpp"
#include "Server/Zone/Packets/Ragexe/20171108/PacketHandlerRagexe20171108.hpp"
#include "Server/Zone/Packets/RE/20171108/PacketsRE20171108.hpp"
#include "Server/Zone/Packets/RE/20171108/PacketHandlerRE20171108.hpp"
#include "Server/Zone/Packets/Zero/20171109/PacketsZero20171109.hpp"
#include "Server/Zone/Packets/Zero/20171109/PacketHandlerZero20171109.hpp"
#include "Server/Zone/Packets/Zero/20171113/PacketsZero20171113.hpp"
#include "Server/Zone/Packets/Zero/20171113/PacketHandlerZero20171113.hpp"
#include "Server/Zone/Packets/Ragexe/20171115/PacketsRagexe20171115.hpp"
#include "Server/Zone/Packets/Ragexe/20171115/PacketHandlerRagexe20171115.hpp"
#include "Server/Zone/Packets/RE/20171115/PacketsRE20171115.hpp"
#include "Server/Zone/Packets/RE/20171115/PacketHandlerRE20171115.hpp"
#include "Server/Zone/Packets/Zero/20171115/PacketsZero20171115.hpp"
#include "Server/Zone/Packets/Zero/20171115/PacketHandlerZero20171115.hpp"
#include "Server/Zone/Packets/Zero/20171116/PacketsZero20171116.hpp"
#include "Server/Zone/Packets/Zero/20171116/PacketHandlerZero20171116.hpp"
#include "Server/Zone/Packets/Zero/20171117/PacketsZero20171117.hpp"
#include "Server/Zone/Packets/Zero/20171117/PacketHandlerZero20171117.hpp"
#include "Server/Zone/Packets/Zero/20171121/PacketsZero20171121.hpp"
#include "Server/Zone/Packets/Zero/20171121/PacketHandlerZero20171121.hpp"
#include "Server/Zone/Packets/Ragexe/20171122/PacketsRagexe20171122.hpp"
#include "Server/Zone/Packets/Ragexe/20171122/PacketHandlerRagexe20171122.hpp"
#include "Server/Zone/Packets/RE/20171122/PacketsRE20171122.hpp"
#include "Server/Zone/Packets/RE/20171122/PacketHandlerRE20171122.hpp"
#include "Server/Zone/Packets/Zero/20171122/PacketsZero20171122.hpp"
#include "Server/Zone/Packets/Zero/20171122/PacketHandlerZero20171122.hpp"
#include "Server/Zone/Packets/Zero/20171123/PacketsZero20171123.hpp"
#include "Server/Zone/Packets/Zero/20171123/PacketHandlerZero20171123.hpp"
#include "Server/Zone/Packets/Zero/20171127/PacketsZero20171127.hpp"
#include "Server/Zone/Packets/Zero/20171127/PacketHandlerZero20171127.hpp"
#include "Server/Zone/Packets/Zero/20171128/PacketsZero20171128.hpp"
#include "Server/Zone/Packets/Zero/20171128/PacketHandlerZero20171128.hpp"
#include "Server/Zone/Packets/Ragexe/20171129/PacketsRagexe20171129.hpp"
#include "Server/Zone/Packets/Ragexe/20171129/PacketHandlerRagexe20171129.hpp"
#include "Server/Zone/Packets/RE/20171129/PacketsRE20171129.hpp"
#include "Server/Zone/Packets/RE/20171129/PacketHandlerRE20171129.hpp"
#include "Server/Zone/Packets/Zero/20171130/PacketsZero20171130.hpp"
#include "Server/Zone/Packets/Zero/20171130/PacketHandlerZero20171130.hpp"
#include "Server/Zone/Packets/Zero/20171204/PacketsZero20171204.hpp"
#include "Server/Zone/Packets/Zero/20171204/PacketHandlerZero20171204.hpp"
#include "Server/Zone/Packets/Ragexe/20171206/PacketsRagexe20171206.hpp"
#include "Server/Zone/Packets/Ragexe/20171206/PacketHandlerRagexe20171206.hpp"
#include "Server/Zone/Packets/RE/20171206/PacketsRE20171206.hpp"
#include "Server/Zone/Packets/RE/20171206/PacketHandlerRE20171206.hpp"
#include "Server/Zone/Packets/Zero/20171206/PacketsZero20171206.hpp"
#include "Server/Zone/Packets/Zero/20171206/PacketHandlerZero20171206.hpp"
#include "Server/Zone/Packets/Zero/20171208/PacketsZero20171208.hpp"
#include "Server/Zone/Packets/Zero/20171208/PacketHandlerZero20171208.hpp"
#include "Server/Zone/Packets/Zero/20171209/PacketsZero20171209.hpp"
#include "Server/Zone/Packets/Zero/20171209/PacketHandlerZero20171209.hpp"
#include "Server/Zone/Packets/Zero/20171210/PacketsZero20171210.hpp"
#include "Server/Zone/Packets/Zero/20171210/PacketHandlerZero20171210.hpp"
#include "Server/Zone/Packets/Zero/20171211/PacketsZero20171211.hpp"
#include "Server/Zone/Packets/Zero/20171211/PacketHandlerZero20171211.hpp"
#include "Server/Zone/Packets/Zero/20171212/PacketsZero20171212.hpp"
#include "Server/Zone/Packets/Zero/20171212/PacketHandlerZero20171212.hpp"
#include "Server/Zone/Packets/Ragexe/20171213/PacketsRagexe20171213.hpp"
#include "Server/Zone/Packets/Ragexe/20171213/PacketHandlerRagexe20171213.hpp"
#include "Server/Zone/Packets/RE/20171213/PacketsRE20171213.hpp"
#include "Server/Zone/Packets/RE/20171213/PacketHandlerRE20171213.hpp"
#include "Server/Zone/Packets/Zero/20171213/PacketsZero20171213.hpp"
#include "Server/Zone/Packets/Zero/20171213/PacketHandlerZero20171213.hpp"
#include "Server/Zone/Packets/Zero/20171214/PacketsZero20171214.hpp"
#include "Server/Zone/Packets/Zero/20171214/PacketHandlerZero20171214.hpp"
#include "Server/Zone/Packets/Ragexe/20171220/PacketsRagexe20171220.hpp"
#include "Server/Zone/Packets/Ragexe/20171220/PacketHandlerRagexe20171220.hpp"
#include "Server/Zone/Packets/RE/20171220/PacketsRE20171220.hpp"
#include "Server/Zone/Packets/RE/20171220/PacketHandlerRE20171220.hpp"
#include "Server/Zone/Packets/Zero/20171220/PacketsZero20171220.hpp"
#include "Server/Zone/Packets/Zero/20171220/PacketHandlerZero20171220.hpp"
#include "Server/Zone/Packets/Zero/20171221/PacketsZero20171221.hpp"
#include "Server/Zone/Packets/Zero/20171221/PacketHandlerZero20171221.hpp"
#include "Server/Zone/Packets/Ragexe/20171227/PacketsRagexe20171227.hpp"
#include "Server/Zone/Packets/Ragexe/20171227/PacketHandlerRagexe20171227.hpp"
#include "Server/Zone/Packets/RE/20171227/PacketsRE20171227.hpp"
#include "Server/Zone/Packets/RE/20171227/PacketHandlerRE20171227.hpp"
#include "Server/Zone/Packets/Zero/20171227/PacketsZero20171227.hpp"
#include "Server/Zone/Packets/Zero/20171227/PacketHandlerZero20171227.hpp"
#include "Server/Zone/Packets/Zero/20171229/PacketsZero20171229.hpp"
#include "Server/Zone/Packets/Zero/20171229/PacketHandlerZero20171229.hpp"
#include "Server/Zone/Packets/Ragexe/20180103/PacketsRagexe20180103.hpp"
#include "Server/Zone/Packets/Ragexe/20180103/PacketHandlerRagexe20180103.hpp"
#include "Server/Zone/Packets/RE/20180103/PacketsRE20180103.hpp"
#include "Server/Zone/Packets/RE/20180103/PacketHandlerRE20180103.hpp"
#include "Server/Zone/Packets/Zero/20180103/PacketsZero20180103.hpp"
#include "Server/Zone/Packets/Zero/20180103/PacketHandlerZero20180103.hpp"
#include "Server/Zone/Packets/Ragexe/20180117/PacketsRagexe20180117.hpp"
#include "Server/Zone/Packets/Ragexe/20180117/PacketHandlerRagexe20180117.hpp"
#include "Server/Zone/Packets/RE/20180117/PacketsRE20180117.hpp"
#include "Server/Zone/Packets/RE/20180117/PacketHandlerRE20180117.hpp"
#include "Server/Zone/Packets/Zero/20180117/PacketsZero20180117.hpp"
#include "Server/Zone/Packets/Zero/20180117/PacketHandlerZero20180117.hpp"
#include "Server/Zone/Packets/Ragexe/20180124/PacketsRagexe20180124.hpp"
#include "Server/Zone/Packets/Ragexe/20180124/PacketHandlerRagexe20180124.hpp"
#include "Server/Zone/Packets/RE/20180124/PacketsRE20180124.hpp"
#include "Server/Zone/Packets/RE/20180124/PacketHandlerRE20180124.hpp"
#include "Server/Zone/Packets/Ragexe/20180131/PacketsRagexe20180131.hpp"
#include "Server/Zone/Packets/Ragexe/20180131/PacketHandlerRagexe20180131.hpp"
#include "Server/Zone/Packets/Zero/20180131/PacketsZero20180131.hpp"
#include "Server/Zone/Packets/Zero/20180131/PacketHandlerZero20180131.hpp"
#include "Server/Zone/Packets/Ragexe/20180207/PacketsRagexe20180207.hpp"
#include "Server/Zone/Packets/Ragexe/20180207/PacketHandlerRagexe20180207.hpp"
#include "Server/Zone/Packets/RE/20180207/PacketsRE20180207.hpp"
#include "Server/Zone/Packets/RE/20180207/PacketHandlerRE20180207.hpp"
#include "Server/Zone/Packets/Zero/20180207/PacketsZero20180207.hpp"
#include "Server/Zone/Packets/Zero/20180207/PacketHandlerZero20180207.hpp"
#include "Server/Zone/Packets/Ragexe/20180213/PacketsRagexe20180213.hpp"
#include "Server/Zone/Packets/Ragexe/20180213/PacketHandlerRagexe20180213.hpp"
#include "Server/Zone/Packets/RE/20180213/PacketsRE20180213.hpp"
#include "Server/Zone/Packets/RE/20180213/PacketHandlerRE20180213.hpp"
#include "Server/Zone/Packets/Zero/20180213/PacketsZero20180213.hpp"
#include "Server/Zone/Packets/Zero/20180213/PacketHandlerZero20180213.hpp"
#include "Server/Zone/Packets/Ragexe/20180221/PacketsRagexe20180221.hpp"
#include "Server/Zone/Packets/Ragexe/20180221/PacketHandlerRagexe20180221.hpp"
#include "Server/Zone/Packets/RE/20180221/PacketsRE20180221.hpp"
#include "Server/Zone/Packets/RE/20180221/PacketHandlerRE20180221.hpp"
#include "Server/Zone/Packets/Zero/20180221/PacketsZero20180221.hpp"
#include "Server/Zone/Packets/Zero/20180221/PacketHandlerZero20180221.hpp"
#include "Server/Zone/Packets/Zero/20180228/PacketsZero20180228.hpp"
#include "Server/Zone/Packets/Zero/20180228/PacketHandlerZero20180228.hpp"
#include "Server/Zone/Packets/Ragexe/20180307/PacketsRagexe20180307.hpp"
#include "Server/Zone/Packets/Ragexe/20180307/PacketHandlerRagexe20180307.hpp"
#include "Server/Zone/Packets/RE/20180307/PacketsRE20180307.hpp"
#include "Server/Zone/Packets/RE/20180307/PacketHandlerRE20180307.hpp"
#include "Server/Zone/Packets/Zero/20180307/PacketsZero20180307.hpp"
#include "Server/Zone/Packets/Zero/20180307/PacketHandlerZero20180307.hpp"
#include "Server/Zone/Packets/Ragexe/20180309/PacketsRagexe20180309.hpp"
#include "Server/Zone/Packets/Ragexe/20180309/PacketHandlerRagexe20180309.hpp"
#include "Server/Zone/Packets/Zero/20180309/PacketsZero20180309.hpp"
#include "Server/Zone/Packets/Zero/20180309/PacketHandlerZero20180309.hpp"
#include "Server/Zone/Packets/Ragexe/20180314/PacketsRagexe20180314.hpp"
#include "Server/Zone/Packets/Ragexe/20180314/PacketHandlerRagexe20180314.hpp"
#include "Server/Zone/Packets/Zero/20180314/PacketsZero20180314.hpp"
#include "Server/Zone/Packets/Zero/20180314/PacketHandlerZero20180314.hpp"
#include "Server/Zone/Packets/Ragexe/20180315/PacketsRagexe20180315.hpp"
#include "Server/Zone/Packets/Ragexe/20180315/PacketHandlerRagexe20180315.hpp"
#include "Server/Zone/Packets/Zero/20180315/PacketsZero20180315.hpp"
#include "Server/Zone/Packets/Zero/20180315/PacketHandlerZero20180315.hpp"
#include "Server/Zone/Packets/Ragexe/20180321/PacketsRagexe20180321.hpp"
#include "Server/Zone/Packets/Ragexe/20180321/PacketHandlerRagexe20180321.hpp"
#include "Server/Zone/Packets/RE/20180321/PacketsRE20180321.hpp"
#include "Server/Zone/Packets/RE/20180321/PacketHandlerRE20180321.hpp"
#include "Server/Zone/Packets/Zero/20180321/PacketsZero20180321.hpp"
#include "Server/Zone/Packets/Zero/20180321/PacketHandlerZero20180321.hpp"
#include "Server/Zone/Packets/Ragexe/20180328/PacketsRagexe20180328.hpp"
#include "Server/Zone/Packets/Ragexe/20180328/PacketHandlerRagexe20180328.hpp"
#include "Server/Zone/Packets/RE/20180328/PacketsRE20180328.hpp"
#include "Server/Zone/Packets/RE/20180328/PacketHandlerRE20180328.hpp"
#include "Server/Zone/Packets/Zero/20180328/PacketsZero20180328.hpp"
#include "Server/Zone/Packets/Zero/20180328/PacketHandlerZero20180328.hpp"
#include "Server/Zone/Packets/Ragexe/20180404/PacketsRagexe20180404.hpp"
#include "Server/Zone/Packets/Ragexe/20180404/PacketHandlerRagexe20180404.hpp"
#include "Server/Zone/Packets/RE/20180404/PacketsRE20180404.hpp"
#include "Server/Zone/Packets/RE/20180404/PacketHandlerRE20180404.hpp"
#include "Server/Zone/Packets/Zero/20180411/PacketsZero20180411.hpp"
#include "Server/Zone/Packets/Zero/20180411/PacketHandlerZero20180411.hpp"
#include "Server/Zone/Packets/Ragexe/20180418/PacketsRagexe20180418.hpp"
#include "Server/Zone/Packets/Ragexe/20180418/PacketHandlerRagexe20180418.hpp"
#include "Server/Zone/Packets/RE/20180418/PacketsRE20180418.hpp"
#include "Server/Zone/Packets/RE/20180418/PacketHandlerRE20180418.hpp"
#include "Server/Zone/Packets/Ragexe/20180425/PacketsRagexe20180425.hpp"
#include "Server/Zone/Packets/Ragexe/20180425/PacketHandlerRagexe20180425.hpp"
#include "Server/Zone/Packets/RE/20180425/PacketsRE20180425.hpp"
#include "Server/Zone/Packets/RE/20180425/PacketHandlerRE20180425.hpp"
#include "Server/Zone/Packets/Zero/20180425/PacketsZero20180425.hpp"
#include "Server/Zone/Packets/Zero/20180425/PacketHandlerZero20180425.hpp"
#include "Server/Zone/Packets/Ragexe/20180502/PacketsRagexe20180502.hpp"
#include "Server/Zone/Packets/Ragexe/20180502/PacketHandlerRagexe20180502.hpp"
#include "Server/Zone/Packets/RE/20180502/PacketsRE20180502.hpp"
#include "Server/Zone/Packets/RE/20180502/PacketHandlerRE20180502.hpp"
#include "Server/Zone/Packets/Ragexe/20180509/PacketsRagexe20180509.hpp"
#include "Server/Zone/Packets/Ragexe/20180509/PacketHandlerRagexe20180509.hpp"
#include "Server/Zone/Packets/Zero/20180509/PacketsZero20180509.hpp"
#include "Server/Zone/Packets/Zero/20180509/PacketHandlerZero20180509.hpp"
#include "Server/Zone/Packets/Zero/20180511/PacketsZero20180511.hpp"
#include "Server/Zone/Packets/Zero/20180511/PacketHandlerZero20180511.hpp"
#include "Server/Zone/Packets/Ragexe/20180516/PacketsRagexe20180516.hpp"
#include "Server/Zone/Packets/Ragexe/20180516/PacketHandlerRagexe20180516.hpp"
#include "Server/Zone/Packets/RE/20180516/PacketsRE20180516.hpp"
#include "Server/Zone/Packets/RE/20180516/PacketHandlerRE20180516.hpp"
#include "Server/Zone/Packets/Ragexe/20180523/PacketsRagexe20180523.hpp"
#include "Server/Zone/Packets/Ragexe/20180523/PacketHandlerRagexe20180523.hpp"
#include "Server/Zone/Packets/RE/20180523/PacketsRE20180523.hpp"
#include "Server/Zone/Packets/RE/20180523/PacketHandlerRE20180523.hpp"
#include "Server/Zone/Packets/Zero/20180523/PacketsZero20180523.hpp"
#include "Server/Zone/Packets/Zero/20180523/PacketHandlerZero20180523.hpp"
#include "Server/Zone/Packets/Ragexe/20180530/PacketsRagexe20180530.hpp"
#include "Server/Zone/Packets/Ragexe/20180530/PacketHandlerRagexe20180530.hpp"
#include "Server/Zone/Packets/RE/20180530/PacketsRE20180530.hpp"
#include "Server/Zone/Packets/RE/20180530/PacketHandlerRE20180530.hpp"
#include "Server/Zone/Packets/Ragexe/20180605/PacketsRagexe20180605.hpp"
#include "Server/Zone/Packets/Ragexe/20180605/PacketHandlerRagexe20180605.hpp"
#include "Server/Zone/Packets/RE/20180605/PacketsRE20180605.hpp"
#include "Server/Zone/Packets/RE/20180605/PacketHandlerRE20180605.hpp"
#include "Server/Zone/Packets/Zero/20180605/PacketsZero20180605.hpp"
#include "Server/Zone/Packets/Zero/20180605/PacketHandlerZero20180605.hpp"
#include "Server/Zone/Packets/RE/20180612/PacketsRE20180612.hpp"
#include "Server/Zone/Packets/RE/20180612/PacketHandlerRE20180612.hpp"
#include "Server/Zone/Packets/Ragexe/20180620/PacketsRagexe20180620.hpp"
#include "Server/Zone/Packets/Ragexe/20180620/PacketHandlerRagexe20180620.hpp"
#include "Server/Zone/Packets/RE/20180620/PacketsRE20180620.hpp"
#include "Server/Zone/Packets/RE/20180620/PacketHandlerRE20180620.hpp"
#include "Server/Zone/Packets/Ragexe/20180621/PacketsRagexe20180621.hpp"
#include "Server/Zone/Packets/Ragexe/20180621/PacketHandlerRagexe20180621.hpp"
#include "Server/Zone/Packets/RE/20180621/PacketsRE20180621.hpp"
#include "Server/Zone/Packets/RE/20180621/PacketHandlerRE20180621.hpp"
#include "Server/Zone/Packets/Zero/20180627/PacketsZero20180627.hpp"
#include "Server/Zone/Packets/Zero/20180627/PacketHandlerZero20180627.hpp"
#include "Server/Zone/Packets/Zero/20180703/PacketsZero20180703.hpp"
#include "Server/Zone/Packets/Zero/20180703/PacketHandlerZero20180703.hpp"
#include "Server/Zone/Packets/Ragexe/20180704/PacketsRagexe20180704.hpp"
#include "Server/Zone/Packets/Ragexe/20180704/PacketHandlerRagexe20180704.hpp"
#include "Server/Zone/Packets/RE/20180704/PacketsRE20180704.hpp"
#include "Server/Zone/Packets/RE/20180704/PacketHandlerRE20180704.hpp"
#include "Server/Zone/Packets/RE/20180711/PacketsRE20180711.hpp"
#include "Server/Zone/Packets/RE/20180711/PacketHandlerRE20180711.hpp"
#include "Server/Zone/Packets/Zero/20180711/PacketsZero20180711.hpp"
#include "Server/Zone/Packets/Zero/20180711/PacketHandlerZero20180711.hpp"
#include "Server/Zone/Packets/Ragexe/20180718/PacketsRagexe20180718.hpp"
#include "Server/Zone/Packets/Ragexe/20180718/PacketHandlerRagexe20180718.hpp"
#include "Server/Zone/Packets/RE/20180718/PacketsRE20180718.hpp"
#include "Server/Zone/Packets/RE/20180718/PacketHandlerRE20180718.hpp"
#include "Server/Zone/Packets/Zero/20180725/PacketsZero20180725.hpp"
#include "Server/Zone/Packets/Zero/20180725/PacketHandlerZero20180725.hpp"
#include "Server/Zone/Packets/Ragexe/20180801/PacketsRagexe20180801.hpp"
#include "Server/Zone/Packets/Ragexe/20180801/PacketHandlerRagexe20180801.hpp"
#include "Server/Zone/Packets/RE/20180801/PacketsRE20180801.hpp"
#include "Server/Zone/Packets/RE/20180801/PacketHandlerRE20180801.hpp"
#include "Server/Zone/Packets/Zero/20180801/PacketsZero20180801.hpp"
#include "Server/Zone/Packets/Zero/20180801/PacketHandlerZero20180801.hpp"
#include "Server/Zone/Packets/Ragexe/20180808/PacketsRagexe20180808.hpp"
#include "Server/Zone/Packets/Ragexe/20180808/PacketHandlerRagexe20180808.hpp"
#include "Server/Zone/Packets/RE/20180808/PacketsRE20180808.hpp"
#include "Server/Zone/Packets/RE/20180808/PacketHandlerRE20180808.hpp"
#include "Server/Zone/Packets/Zero/20180808/PacketsZero20180808.hpp"
#include "Server/Zone/Packets/Zero/20180808/PacketHandlerZero20180808.hpp"
#include "Server/Zone/Packets/Ragexe/20180822/PacketsRagexe20180822.hpp"
#include "Server/Zone/Packets/Ragexe/20180822/PacketHandlerRagexe20180822.hpp"
#include "Server/Zone/Packets/RE/20180822/PacketsRE20180822.hpp"
#include "Server/Zone/Packets/RE/20180822/PacketHandlerRE20180822.hpp"
#include "Server/Zone/Packets/Zero/20180822/PacketsZero20180822.hpp"
#include "Server/Zone/Packets/Zero/20180822/PacketHandlerZero20180822.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/PacketsRagexe20180829.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/PacketHandlerRagexe20180829.hpp"
#include "Server/Zone/Packets/RE/20180829/PacketsRE20180829.hpp"
#include "Server/Zone/Packets/RE/20180829/PacketHandlerRE20180829.hpp"
#include "Server/Zone/Packets/Zero/20180829/PacketsZero20180829.hpp"
#include "Server/Zone/Packets/Zero/20180829/PacketHandlerZero20180829.hpp"
#include "Server/Zone/Packets/Ragexe/20180831/PacketsRagexe20180831.hpp"
#include "Server/Zone/Packets/Ragexe/20180831/PacketHandlerRagexe20180831.hpp"
#include "Server/Zone/Packets/Zero/20180905/PacketsZero20180905.hpp"
#include "Server/Zone/Packets/Zero/20180905/PacketHandlerZero20180905.hpp"
#include "Server/Zone/Packets/Ragexe/20180912/PacketsRagexe20180912.hpp"
#include "Server/Zone/Packets/Ragexe/20180912/PacketHandlerRagexe20180912.hpp"
#include "Server/Zone/Packets/RE/20180912/PacketsRE20180912.hpp"
#include "Server/Zone/Packets/RE/20180912/PacketHandlerRE20180912.hpp"
#include "Server/Zone/Packets/Zero/20180912/PacketsZero20180912.hpp"
#include "Server/Zone/Packets/Zero/20180912/PacketHandlerZero20180912.hpp"
#include "Server/Zone/Packets/Ragexe/20180919/PacketsRagexe20180919.hpp"
#include "Server/Zone/Packets/Ragexe/20180919/PacketHandlerRagexe20180919.hpp"
#include "Server/Zone/Packets/RE/20180919/PacketsRE20180919.hpp"
#include "Server/Zone/Packets/RE/20180919/PacketHandlerRE20180919.hpp"
#include "Server/Zone/Packets/Zero/20180919/PacketsZero20180919.hpp"
#include "Server/Zone/Packets/Zero/20180919/PacketHandlerZero20180919.hpp"
#include "Server/Zone/Packets/Zero/20180928/PacketsZero20180928.hpp"
#include "Server/Zone/Packets/Zero/20180928/PacketHandlerZero20180928.hpp"
#include "Server/Zone/Packets/Ragexe/20181002/PacketsRagexe20181002.hpp"
#include "Server/Zone/Packets/Ragexe/20181002/PacketHandlerRagexe20181002.hpp"
#include "Server/Zone/Packets/RE/20181002/PacketsRE20181002.hpp"
#include "Server/Zone/Packets/RE/20181002/PacketHandlerRE20181002.hpp"
#include "Server/Zone/Packets/Zero/20181010/PacketsZero20181010.hpp"
#include "Server/Zone/Packets/Zero/20181010/PacketHandlerZero20181010.hpp"
#include "Server/Zone/Packets/Ragexe/20181017/PacketsRagexe20181017.hpp"
#include "Server/Zone/Packets/Ragexe/20181017/PacketHandlerRagexe20181017.hpp"
#include "Server/Zone/Packets/RE/20181017/PacketsRE20181017.hpp"
#include "Server/Zone/Packets/RE/20181017/PacketHandlerRE20181017.hpp"
#include "Server/Zone/Packets/Ragexe/20181024/PacketsRagexe20181024.hpp"
#include "Server/Zone/Packets/Ragexe/20181024/PacketHandlerRagexe20181024.hpp"
#include "Server/Zone/Packets/Zero/20181024/PacketsZero20181024.hpp"
#include "Server/Zone/Packets/Zero/20181024/PacketHandlerZero20181024.hpp"
#include "Server/Zone/Packets/Ragexe/20181031/PacketsRagexe20181031.hpp"
#include "Server/Zone/Packets/Ragexe/20181031/PacketHandlerRagexe20181031.hpp"
#include "Server/Zone/Packets/RE/20181031/PacketsRE20181031.hpp"
#include "Server/Zone/Packets/RE/20181031/PacketHandlerRE20181031.hpp"
#include "Server/Zone/Packets/Ragexe/20181107/PacketsRagexe20181107.hpp"
#include "Server/Zone/Packets/Ragexe/20181107/PacketHandlerRagexe20181107.hpp"
#include "Server/Zone/Packets/RE/20181107/PacketsRE20181107.hpp"
#include "Server/Zone/Packets/RE/20181107/PacketHandlerRE20181107.hpp"
#include "Server/Zone/Packets/Ragexe/20181114/PacketsRagexe20181114.hpp"
#include "Server/Zone/Packets/Ragexe/20181114/PacketHandlerRagexe20181114.hpp"
#include "Server/Zone/Packets/RE/20181114/PacketsRE20181114.hpp"
#include "Server/Zone/Packets/RE/20181114/PacketHandlerRE20181114.hpp"
#include "Server/Zone/Packets/Zero/20181114/PacketsZero20181114.hpp"
#include "Server/Zone/Packets/Zero/20181114/PacketHandlerZero20181114.hpp"
#include "Server/Zone/Packets/Zero/20181120/PacketsZero20181120.hpp"
#include "Server/Zone/Packets/Zero/20181120/PacketHandlerZero20181120.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/PacketsRagexe20181121.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/PacketHandlerRagexe20181121.hpp"
#include "Server/Zone/Packets/RE/20181121/PacketsRE20181121.hpp"
#include "Server/Zone/Packets/RE/20181121/PacketHandlerRE20181121.hpp"
#include "Server/Zone/Packets/Ragexe/20181128/PacketsRagexe20181128.hpp"
#include "Server/Zone/Packets/Ragexe/20181128/PacketHandlerRagexe20181128.hpp"
#include "Server/Zone/Packets/RE/20181128/PacketsRE20181128.hpp"
#include "Server/Zone/Packets/RE/20181128/PacketHandlerRE20181128.hpp"
#include "Server/Zone/Packets/Zero/20181128/PacketsZero20181128.hpp"
#include "Server/Zone/Packets/Zero/20181128/PacketHandlerZero20181128.hpp"
#include "Server/Zone/Packets/Ragexe/20181205/PacketsRagexe20181205.hpp"
#include "Server/Zone/Packets/Ragexe/20181205/PacketHandlerRagexe20181205.hpp"
#include "Server/Zone/Packets/RE/20181205/PacketsRE20181205.hpp"
#include "Server/Zone/Packets/RE/20181205/PacketHandlerRE20181205.hpp"
#include "Server/Zone/Packets/Ragexe/20181212/PacketsRagexe20181212.hpp"
#include "Server/Zone/Packets/Ragexe/20181212/PacketHandlerRagexe20181212.hpp"
#include "Server/Zone/Packets/RE/20181212/PacketsRE20181212.hpp"
#include "Server/Zone/Packets/RE/20181212/PacketHandlerRE20181212.hpp"
#include "Server/Zone/Packets/Zero/20181212/PacketsZero20181212.hpp"
#include "Server/Zone/Packets/Zero/20181212/PacketHandlerZero20181212.hpp"
#include "Server/Zone/Packets/Ragexe/20181219/PacketsRagexe20181219.hpp"
#include "Server/Zone/Packets/Ragexe/20181219/PacketHandlerRagexe20181219.hpp"
#include "Server/Zone/Packets/RE/20181219/PacketsRE20181219.hpp"
#include "Server/Zone/Packets/RE/20181219/PacketHandlerRE20181219.hpp"
#include "Server/Zone/Packets/Zero/20181219/PacketsZero20181219.hpp"
#include "Server/Zone/Packets/Zero/20181219/PacketHandlerZero20181219.hpp"
#include "Server/Zone/Packets/Ragexe/20181226/PacketsRagexe20181226.hpp"
#include "Server/Zone/Packets/Ragexe/20181226/PacketHandlerRagexe20181226.hpp"
#include "Server/Zone/Packets/RE/20181226/PacketsRE20181226.hpp"
#include "Server/Zone/Packets/RE/20181226/PacketHandlerRE20181226.hpp"
#include "Server/Zone/Packets/Zero/20181226/PacketsZero20181226.hpp"
#include "Server/Zone/Packets/Zero/20181226/PacketHandlerZero20181226.hpp"
#include "Server/Zone/Packets/Ragexe/20190109/PacketsRagexe20190109.hpp"
#include "Server/Zone/Packets/Ragexe/20190109/PacketHandlerRagexe20190109.hpp"
#include "Server/Zone/Packets/RE/20190109/PacketsRE20190109.hpp"
#include "Server/Zone/Packets/RE/20190109/PacketHandlerRE20190109.hpp"
#include "Server/Zone/Packets/Ragexe/20190116/PacketsRagexe20190116.hpp"
#include "Server/Zone/Packets/Ragexe/20190116/PacketHandlerRagexe20190116.hpp"
#include "Server/Zone/Packets/RE/20190116/PacketsRE20190116.hpp"
#include "Server/Zone/Packets/RE/20190116/PacketHandlerRE20190116.hpp"
#include "Server/Zone/Packets/Zero/20190116/PacketsZero20190116.hpp"
#include "Server/Zone/Packets/Zero/20190116/PacketHandlerZero20190116.hpp"
#include "Server/Zone/Packets/Zero/20190117/PacketsZero20190117.hpp"
#include "Server/Zone/Packets/Zero/20190117/PacketHandlerZero20190117.hpp"
#include "Server/Zone/Packets/Ragexe/20190123/PacketsRagexe20190123.hpp"
#include "Server/Zone/Packets/Ragexe/20190123/PacketHandlerRagexe20190123.hpp"
#include "Server/Zone/Packets/RE/20190123/PacketsRE20190123.hpp"
#include "Server/Zone/Packets/RE/20190123/PacketHandlerRE20190123.hpp"
#include "Server/Zone/Packets/Zero/20190130/PacketsZero20190130.hpp"
#include "Server/Zone/Packets/Zero/20190130/PacketHandlerZero20190130.hpp"

#include <memory>


using namespace Horizon::Zone;

PacketHandlerFactory::PacketHandlerFactory()
{
//
}

PacketHandlerFactory::~PacketHandlerFactory()
{
//
}

/**
 * @brief Build a PacketHandler instance for a client (player) connection.
 * @param[in|out] session    shared_ptr to a Session instance.
 * @return shared pointer to a new instance of Horizon::Zone::PacketHandler.
 */
std::shared_ptr<PacketHandler> PacketHandlerFactory::create_packet_handler(std::shared_ptr<ZoneSocket> socket, client_types client_type, uint32_t packet_ver)
{
	if (packet_ver >= 20190130) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20190130>(socket);
	}

	if (packet_ver >= 20190123) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20190123>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20190123>(socket);
	}

	if (packet_ver >= 20190117) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20190117>(socket);
	}

	if (packet_ver >= 20190116) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20190116>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20190116>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20190116>(socket);
	}

	if (packet_ver >= 20190109) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20190109>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20190109>(socket);
	}

	if (packet_ver >= 20181226) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181226>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20181226>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20181226>(socket);
	}

	if (packet_ver >= 20181219) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181219>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20181219>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20181219>(socket);
	}

	if (packet_ver >= 20181212) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181212>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20181212>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20181212>(socket);
	}

	if (packet_ver >= 20181205) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181205>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20181205>(socket);
	}

	if (packet_ver >= 20181128) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181128>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20181128>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20181128>(socket);
	}

	if (packet_ver >= 20181121) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181121>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20181121>(socket);
	}

	if (packet_ver >= 20181120) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20181120>(socket);
	}

	if (packet_ver >= 20181114) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181114>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20181114>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20181114>(socket);
	}

	if (packet_ver >= 20181107) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181107>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20181107>(socket);
	}

	if (packet_ver >= 20181031) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181031>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20181031>(socket);
	}

	if (packet_ver >= 20181024) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181024>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20181024>(socket);
	}

	if (packet_ver >= 20181017) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181017>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20181017>(socket);
	}

	if (packet_ver >= 20181010) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20181010>(socket);
	}

	if (packet_ver >= 20181002) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181002>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20181002>(socket);
	}

	if (packet_ver >= 20180928) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180928>(socket);
	}

	if (packet_ver >= 20180919) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180919>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180919>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180919>(socket);
	}

	if (packet_ver >= 20180912) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180912>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180912>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180912>(socket);
	}

	if (packet_ver >= 20180905) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180905>(socket);
	}

	if (packet_ver >= 20180831) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180831>(socket);
	}

	if (packet_ver >= 20180829) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180829>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180829>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180829>(socket);
	}

	if (packet_ver >= 20180822) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180822>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180822>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180822>(socket);
	}

	if (packet_ver >= 20180808) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180808>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180808>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180808>(socket);
	}

	if (packet_ver >= 20180801) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180801>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180801>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180801>(socket);
	}

	if (packet_ver >= 20180725) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180725>(socket);
	}

	if (packet_ver >= 20180718) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180718>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180718>(socket);
	}

	if (packet_ver >= 20180711) {
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180711>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180711>(socket);
	}

	if (packet_ver >= 20180704) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180704>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180704>(socket);
	}

	if (packet_ver >= 20180703) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180703>(socket);
	}

	if (packet_ver >= 20180627) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180627>(socket);
	}

	if (packet_ver >= 20180621) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180621>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180621>(socket);
	}

	if (packet_ver >= 20180620) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180620>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180620>(socket);
	}

	if (packet_ver >= 20180612) {
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180612>(socket);
	}

	if (packet_ver >= 20180605) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180605>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180605>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180605>(socket);
	}

	if (packet_ver >= 20180530) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180530>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180530>(socket);
	}

	if (packet_ver >= 20180523) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180523>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180523>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180523>(socket);
	}

	if (packet_ver >= 20180516) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180516>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180516>(socket);
	}

	if (packet_ver >= 20180511) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180511>(socket);
	}

	if (packet_ver >= 20180509) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180509>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180509>(socket);
	}

	if (packet_ver >= 20180502) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180502>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180502>(socket);
	}

	if (packet_ver >= 20180425) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180425>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180425>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180425>(socket);
	}

	if (packet_ver >= 20180418) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180418>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180418>(socket);
	}

	if (packet_ver >= 20180411) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180411>(socket);
	}

	if (packet_ver >= 20180404) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180404>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180404>(socket);
	}

	if (packet_ver >= 20180328) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180328>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180328>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180328>(socket);
	}

	if (packet_ver >= 20180321) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180321>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180321>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180321>(socket);
	}

	if (packet_ver >= 20180315) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180315>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180315>(socket);
	}

	if (packet_ver >= 20180314) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180314>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180314>(socket);
	}

	if (packet_ver >= 20180309) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180309>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180309>(socket);
	}

	if (packet_ver >= 20180307) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180307>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180307>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180307>(socket);
	}

	if (packet_ver >= 20180228) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180228>(socket);
	}

	if (packet_ver >= 20180221) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180221>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180221>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180221>(socket);
	}

	if (packet_ver >= 20180213) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180213>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180213>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180213>(socket);
	}

	if (packet_ver >= 20180207) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180207>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180207>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180207>(socket);
	}

	if (packet_ver >= 20180131) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180131>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180131>(socket);
	}

	if (packet_ver >= 20180124) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180124>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180124>(socket);
	}

	if (packet_ver >= 20180117) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180117>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180117>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180117>(socket);
	}

	if (packet_ver >= 20180103) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180103>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180103>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180103>(socket);
	}

	if (packet_ver >= 20171229) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171229>(socket);
	}

	if (packet_ver >= 20171227) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171227>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171227>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171227>(socket);
	}

	if (packet_ver >= 20171221) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171221>(socket);
	}

	if (packet_ver >= 20171220) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171220>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171220>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171220>(socket);
	}

	if (packet_ver >= 20171214) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171214>(socket);
	}

	if (packet_ver >= 20171213) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171213>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171213>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171213>(socket);
	}

	if (packet_ver >= 20171212) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171212>(socket);
	}

	if (packet_ver >= 20171211) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171211>(socket);
	}

	if (packet_ver >= 20171210) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171210>(socket);
	}

	if (packet_ver >= 20171209) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171209>(socket);
	}

	if (packet_ver >= 20171208) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171208>(socket);
	}

	if (packet_ver >= 20171206) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171206>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171206>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171206>(socket);
	}

	if (packet_ver >= 20171204) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171204>(socket);
	}

	if (packet_ver >= 20171130) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171130>(socket);
	}

	if (packet_ver >= 20171129) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171129>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171129>(socket);
	}

	if (packet_ver >= 20171128) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171128>(socket);
	}

	if (packet_ver >= 20171127) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171127>(socket);
	}

	if (packet_ver >= 20171123) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171123>(socket);
	}

	if (packet_ver >= 20171122) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171122>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171122>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171122>(socket);
	}

	if (packet_ver >= 20171121) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171121>(socket);
	}

	if (packet_ver >= 20171117) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171117>(socket);
	}

	if (packet_ver >= 20171116) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171116>(socket);
	}

	if (packet_ver >= 20171115) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171115>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171115>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171115>(socket);
	}

	if (packet_ver >= 20171113) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171113>(socket);
	}

	if (packet_ver >= 20171109) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171109>(socket);
	}

	if (packet_ver >= 20171108) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171108>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171108>(socket);
	}

	if (packet_ver >= 20171101) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171101>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171101>(socket);
	}

	if (packet_ver >= 20171031) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171031>(socket);
	}

	if (packet_ver >= 20171030) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171030>(socket);
	}

	if (packet_ver >= 20171027) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171027>(socket);
	}

	if (packet_ver >= 20171025) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171025>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171025>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171025>(socket);
	}

	if (packet_ver >= 20171024) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171024>(socket);
	}

	if (packet_ver >= 20171023) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171023>(socket);
	}

	if (packet_ver >= 20171019) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171019>(socket);
	}

	if (packet_ver >= 20171018) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171018>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171018>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171018>(socket);
	}

	if (packet_ver >= 20171011) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171011>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171011>(socket);
	}

	if (packet_ver >= 20171002) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171002>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171002>(socket);
	}

	if (packet_ver >= 20170927) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170927>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170927>(socket);
	}

	if (packet_ver >= 20170920) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170920>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170920>(socket);
	}

	if (packet_ver >= 20170913) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170913>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170913>(socket);
	}

	if (packet_ver >= 20170906) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170906>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170906>(socket);
	}

	if (packet_ver >= 20170830) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170830>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170830>(socket);
	}

	if (packet_ver >= 20170823) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170823>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170823>(socket);
	}

	if (packet_ver >= 20170816) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170816>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170816>(socket);
	}

	if (packet_ver >= 20170809) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170809>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170809>(socket);
	}

	if (packet_ver >= 20170801) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170801>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170801>(socket);
	}

	if (packet_ver >= 20170726) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170726>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170726>(socket);
	}

	if (packet_ver >= 20170719) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170719>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170719>(socket);
	}

	if (packet_ver >= 20170712) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170712>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170712>(socket);
	}

	if (packet_ver >= 20170705) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170705>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170705>(socket);
	}

	if (packet_ver >= 20170628) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170628>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170628>(socket);
	}

	if (packet_ver >= 20170621) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170621>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170621>(socket);
	}

	if (packet_ver >= 20170614) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170614>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170614>(socket);
	}

	if (packet_ver >= 20170607) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170607>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170607>(socket);
	}

	if (packet_ver >= 20170531) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170531>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170531>(socket);
	}

	if (packet_ver >= 20170524) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170524>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170524>(socket);
	}

	if (packet_ver >= 20170517) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170517>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170517>(socket);
	}

	if (packet_ver >= 20170502) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170502>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170502>(socket);
	}

	if (packet_ver >= 20170426) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170426>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170426>(socket);
	}

	if (packet_ver >= 20170419) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170419>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170419>(socket);
	}

	if (packet_ver >= 20170412) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170412>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170412>(socket);
	}

	if (packet_ver >= 20170405) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170405>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170405>(socket);
	}

	if (packet_ver >= 20170329) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170329>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170329>(socket);
	}

	if (packet_ver >= 20170322) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170322>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170322>(socket);
	}

	if (packet_ver >= 20170315) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170315>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170315>(socket);
	}

	if (packet_ver >= 20170308) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170308>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170308>(socket);
	}

	if (packet_ver >= 20170228) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170228>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170228>(socket);
	}

	if (packet_ver >= 20170222) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170222>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170222>(socket);
	}

	if (packet_ver >= 20170215) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170215>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170215>(socket);
	}

	if (packet_ver >= 20170208) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170208>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170208>(socket);
	}

	if (packet_ver >= 20170201) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170201>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170201>(socket);
	}

	if (packet_ver >= 20170125) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170125>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170125>(socket);
	}

	if (packet_ver >= 20170118) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170118>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170118>(socket);
	}

	if (packet_ver >= 20170111) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170111>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170111>(socket);
	}

	if (packet_ver >= 20170104) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170104>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170104>(socket);
	}

	return std::make_shared<PacketHandler>(socket);
}
