#pragma once

namespace csgo::valve {
    ALWAYS_INLINE void user_cmd_t::sanitize( ) {
        m_view_angles.normalize( );

        constexpr auto k_max_roll = 50.f;

        const auto& cvars = g_ctx->cvars( );

        m_view_angles.x( ) = std::clamp( m_view_angles.x( ), -cvars.m_cl_pitchup->get_float( ), cvars.m_cl_pitchdown->get_float( ) );
        m_view_angles.z( ) = std::clamp( m_view_angles.z( ), -k_max_roll, k_max_roll );

        const auto max_fwd_speed = cvars.m_cl_forwardspeed->get_float( );
        const auto max_side_speed = cvars.m_cl_sidespeed->get_float( );
        const auto max_up_speed = cvars.m_cl_upspeed->get_float( );

        m_move = {
            std::clamp( m_move.x( ), -max_fwd_speed, max_fwd_speed ),
            std::clamp( m_move.y( ), -max_side_speed, max_side_speed ),
            std::clamp( m_move.z( ), -max_up_speed, max_up_speed )
        };
    }

    ALWAYS_INLINE const char* studio_hitbox_set_t::name( ) const {
        return !m_name_index ? nullptr
            : sdk::address_t{ this }.self_offset( m_name_index ).as< const char* >( );
    }

    ALWAYS_INLINE studio_bbox_t* studio_hitbox_set_t::get_bbox( const int i ) const {
        return i > m_hitboxes_count ? nullptr
            : sdk::address_t{ this }.self_offset( m_hitbox_index ).as< studio_bbox_t* >( ) + i;
    }

    ALWAYS_INLINE studio_bone_t* studio_hdr_t::studio_t::get_bone( const int i ) const {
        return i > m_bones_count ? nullptr
            : sdk::address_t{ this }.self_offset( m_bone_index ).as< studio_bone_t* >( ) + i;
    }

    ALWAYS_INLINE studio_hitbox_set_t* studio_hdr_t::studio_t::get_hitbox_set( const int i ) const {
        return i > m_hitbox_sets_count ? nullptr
            : sdk::address_t{ this }.self_offset( m_hitbox_set_index ).as< studio_hitbox_set_t* >( ) + i;
    }
}