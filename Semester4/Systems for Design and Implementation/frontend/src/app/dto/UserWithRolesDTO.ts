import { User } from "../model/User"
import { Role } from "../model/Role"

export interface UserWithRolesDTO {
    user: User,
    role: Role
}